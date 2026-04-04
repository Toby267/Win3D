#include "scene/objects/Materials.hpp"
#include "util/Util.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numbers>

// * -------------------------------------- [ POLYMORPHISM STUFF ] --------------------------------------- * //

Colour Mat::eval(const Material& mat, Vector cameraDirection, Vector lightDirection, Vector normal, Colour colour) {
    return std::visit(Mat::evaluate{lightDirection, cameraDirection, normal, colour}, mat);
}

// * ---------------------------------------- [ DISNEY_DIFFUSE ] ----------------------------------------- * //

Mat::DisneyDiffuse::DisneyDiffuse(double r, double s)
    : roughness(r), subsurface(s)
{ }

//crap
static double SchlickFresnel(double u) {
    float m = std::clamp(1.0-u, 0.0, 1.0);
    return std::pow(m, 5);
}

static double GTR1(double NdotH, double a) {
    if (a >= 1) return std::numbers::inv_pi;
    double a2 = a*a;
    double t = 1 + (a2-1)*NdotH*NdotH;
    return (a2-1) / (std::numbers::pi*std::log(a2)*t);
}

static double GTR2(double NdotH, double a) {
    double a2 = a*a;
    double t = 1 + (a2-1)*NdotH*NdotH;
    return (a2-1) / (std::numbers::pi*t*t);
}

static double GTR2_aniso(double NdotH, double HdotX, double HdotY, double ax, double ay) {
    double x = HdotX/ax, x2 = x*x;
    double y = HdotY/ay, y2 = y*y;

    double factor = x2 + y2 + NdotH*NdotH;
    
    return 1 / (std::numbers::pi * ax*ay * factor * factor);
}

static double smithG_GGX(double NdotV, double alphaG) {
    double a = alphaG*alphaG;
    double b = NdotV*NdotV;
    return 1 / (NdotV + std::sqrt(a + b - a*b));
}

static double smithG_GGX_aniso(double NdotV, double vDotX, double VdotY, double ax, double ay) {
    double x = vDotX*ax, x2 = x*x;
    double y = VdotY*ay, y2 = y*y;
    double n2 = NdotV*NdotV;
    
    return 1 / (NdotV + std::sqrt( x2 + y2 + n2 ));
}

static Vector mon2lin(Colour x) {
    return Vector(std::pow(x.r(), 2.2), std::pow(x.g(), 2.2), std::pow(x.b(), 2.2));
}
//crap

#define mix(a, b, w) (a * (1.0-w) + b * w)

//NOT WORKING BECAUSE YOUR NOT TRANSLATING NORMALS WHEN MOVING OBJECTS TO WORLD SPACE AND CAMERA SPACE AND VIEW VOLUME SPACE
static int i = 0;
Colour Mat::evaluate::operator()(const DisneyBSDF& mat) const {
    // std::cout << "DisneyBSDF\n";
    double asdlkjf = Vector::dotProduct(normal, -in);

    // if ((i++) % 10 == 0)
    // std::cout << "normal, -in: " << normal << ", " << -in << '\n';

    // std::cout << "asdskfjasdl: " << asdlkjf << '\n';

    return colour * asdlkjf;
    
    Vector L = in, V = out, N = normal;

    double NdotL = Vector::dotProduct(N, L);
    double NdotV = Vector::dotProduct(N, V);
    if (NdotL < 0 || NdotV < 0) return Colour(0.0, 0.0, 0.0, 0.0);

    Vector H = L+V;
    H = H.normalise();
    double NdotH = Vector::dotProduct(N, H);
    double LdotH = Vector::dotProduct(L, H);

    Vector Cdlin = mon2lin(colour);
    double Cdlum = 0.3*Cdlin[0] + 0.6*Cdlin[1] + 0.1*Cdlin[2];

    Vector Ctint = Cdlum > 0 ? Cdlin/Cdlum : Vector(1, 1, 1);
    Vector Cspec0 = mix(mix(Vector(1, 1, 1), Ctint, mat.specularTint) * mat.specular * 0.08, Cdlin, mat.metallic);
    Vector Csheen = mix(Vector(1, 1, 1), Ctint, mat.sheenTint);

    double FL = SchlickFresnel(NdotL), FV = SchlickFresnel(NdotV);
    double Fd90 = 0.5 + 2 * LdotH*LdotH * mat.roughness;
    double Fd = mix(1.0, Fd90, FL) * mix (1.0, Fd90, FV);

    double Fss90 = LdotH*LdotH*mat.roughness;
    double Fss = mix(1.0, Fss90, FL) * mix(1.0, Fss90, FV);
    double ss = 1.25 * (Fss * (1 / (NdotL + NdotV) - 0.5) + 0.5);

    double aspect = std::sqrt(mat.anisotropic*0.9);
    double ax = std::max(0.001, (mat.roughness*mat.roughness) / aspect);
    double ay = std::max(0.001, (mat.roughness*mat.roughness) * aspect);
    // double Ds = GTR2_aniso(NdotH, Vector::dotProduct(H, X), Vector::dotProduct(H, Y), ax, ay);
    double FH = SchlickFresnel(LdotH);
    Vector Fs = mix(Cspec0, Vector(1, 1, 1), FH);
    // double Gs = smithG_GGX_aniso(NdotL, Vector::dotProduct(L, X), Vector::dotProduct(L, Y), ax, ay) *
                // smithG_GGX_aniso(NdotL, Vector::dotProduct(V, X), Vector::dotProduct(V, Y), ax, ay);

    Vector Fsheen = Csheen * FH * mat.sheen;

    double Dr = GTR1(NdotH, mix(0.1, 0.001, mat.clearcoatGloss));
    double Fr = mix(0.04, 1.0, FH);
    double Gr = smithG_GGX(NdotL, 0.25) * smithG_GGX(NdotV, 0.25);

    // Vector retval = (Cdlin * std::numbers::inv_pi * mix(Fd, ss, mat.subsurface) + Fsheen)
                    // * (1-mat.metallic)
                    // + Fs*Gs*Ds + 0.25*mat.clearcoat*Gr*Fr*Dr;
    Vector retval = (Cdlin * std::numbers::inv_pi * mix(Fd, ss, mat.subsurface) + Fsheen)
                    * (1-mat.metallic)
                    + Fs + 0.25*mat.clearcoat*Gr*Fr*Dr;

    return Colour(retval[0], retval[1], retval[2]);
}

Colour Mat::evaluate::operator()(const DisneyDiffuse& mat) const {
    // std::cout << "DisneyDiffuse\n";
    // return colour;

    // std::cout << "colour: " << colour << '\n';

    Vector half = in + out;
    half.normalise();
    double cosIn =    std::clamp(   std::abs(Vector::dotProduct(normal, in)), 0.0, 1.0   );
    double cosOut =    std::clamp(   std::abs(Vector::dotProduct(normal, out)), 0.0, 1.0   );
    double hout =    std::clamp(   std::abs(Vector::dotProduct(half, out)), 0.0, 1.0   );
    // std::cout << "cosIn, cosOut, hout: " << cosIn << ", " << cosOut << ", " << hout << '\n';

    //calculate fBaseDiffuse
    double fd90 = 0.5 + 2 * mat.roughness * hout * hout;
    // std::cout << "fd90" <<  ", " << fd90 << '\n';

    double fdIn = std::pow((1 - cosIn), 5);
    fdIn = 1 + (fd90 - 1) * fdIn;
    // std::cout << "fdIn" <<  ", " << fdIn << '\n';

    double fdOut = std::pow((1 - cosOut), 5);
    fdOut = 1 + (fd90 - 1) * fdOut;
    // std::cout << "fdOut" <<  ", " << fdOut << '\n';

    Colour fBaseDiffuse = colour * std::numbers::inv_pi * fdIn * fdOut * cosOut;
    // std::cout << "fBaseDiffuse" << fBaseDiffuse << '\n';
    
    //calculate fSubsurface
    double fss90 = mat.roughness * hout * hout;

    double fssIn = std::pow((1 - cosIn), 5);
    fssIn = 1 + (fss90 - 1) * fssIn;
    // std::cout << "fssIn" <<  ", " << fssIn << '\n';

    double fssOut = std::pow((1 - cosOut), 5);
    fssOut = 1 + (fss90 - 1) * fssOut;
    // std::cout << "fssOut" <<  ", " << fssOut << '\n';

    Colour fSubsurface = colour * 1.25 * std::numbers::inv_pi;
    double term = (1 / (cosIn + cosOut)) - 0.5;
    fSubsurface = fSubsurface * (fssIn * fssOut * term + 0.5) * cosOut;
    // std::cout << "fSubsurface" <<  ", " << fSubsurface << '\n';
    
    //calculate result
    Colour result = fBaseDiffuse * (1 - mat.subsurface) + fSubsurface * fSubsurface;
    // std::cout << "resulting colour: " << result << '\n';
    // result.reNormalise(); // i actually think this is breaking it becuase if one pixel as a colour of 999, 999, 999, and the other has 1, 1, 1, then they will both result in the same colour
    // this means there is a bug somewhere else in here...

    // std::cout << "colour: " << result << '\n';

    // std::cin.get();
    return result;
}

// * ----------------------------------------- [ DISNEY_METAL ] ------------------------------------------ * //

Colour Mat::evaluate::operator()(const DisneyMetal& material) const {
    // std::cout << "DisneyMetal\n";
    return colour;
}
