#include "scene/objects/Materials.hpp"
#include "util/Util.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numbers>

// * -------------------------------------- [ POLYMORPHISM STUFF ] --------------------------------------- * //

Colour Mat::eval(const Material& mat, Vector in, Vector out, Vector normal, Colour colour) {
    // calculate the lambert factor in the rendering equation
    double lambert = std::max(0.0, Vector::dotProduct(in, normal));
    
    // calculate the bxdf of the rendering equation
    float bxdf = std::visit(Mat::evaluate{in, out, normal, colour.normalise()}, mat);

    // incoming light has already been calculated

    // calculate the reflected light in the rendering equaiton
    Colour reflected = colour * lambert * bxdf;

    // ignore alpha stuff
    reflected.a() = 255;

    return reflected;
}

// * ---------------------------------------- [ MATERIALS ] ----------------------------------------- * //

float Mat::evaluate::operator()(const DisneyBSDF& mat) const {
    return 1;
}

float Mat::evaluate::operator()(const DisneyDiffuse& mat) const {
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

    Colour fBaseDiffuse = baseColour * std::numbers::inv_pi * fdIn * fdOut * cosOut;
    // std::cout << "fBaseDiffuse" << fBaseDiffuse << '\n';
    
    //calculate fSubsurface
    double fss90 = mat.roughness * hout * hout;

    double fssIn = std::pow((1 - cosIn), 5);
    fssIn = 1 + (fss90 - 1) * fssIn;
    // std::cout << "fssIn" <<  ", " << fssIn << '\n';

    double fssOut = std::pow((1 - cosOut), 5);
    fssOut = 1 + (fss90 - 1) * fssOut;
    // std::cout << "fssOut" <<  ", " << fssOut << '\n';

    Colour fSubsurface = baseColour * 1.25 * std::numbers::inv_pi;
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
    // return result;
    return 1;
}

float Mat::evaluate::operator()(const DisneyMetal& material) const {
    return 1;
}

float Mat::evaluate::operator()(const DisneyClearcoat& material) const {
    return 1;
}

float Mat::evaluate::operator()(const DisneyGlass& material) const {
    return 1;
}

float Mat::evaluate::operator()(const DisneySheen& material) const {
    return 1;
}
