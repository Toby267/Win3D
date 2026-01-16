#include "scene/Materials.hpp"
#include "util/Colour.hpp"
#include "util/Vector.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numbers>

// * -------------------------------------- [ POLYMORPHISM STUFF ] --------------------------------------- * //

Colour Mat::eval(const Material& mat, Vector cameraDirection, Vector lightDirection, Vector normal, Colour colour) {
    return std::visit(Mat::visitor{lightDirection, cameraDirection, normal, colour}, mat);
}

// * ---------------------------------------- [ DISNEY_DIFFUSE ] ----------------------------------------- * //

Mat::DisneyDiffuse::DisneyDiffuse(double r, double s)
    : roughness(r), subsurface(s)
{ }

Colour Mat::visitor::operator()(const DisneyDiffuse& mat) const {
    // return colour;

    std::cout << "in, out, normal, colour:\n";
    std::cout << in << '\n' << out << '\n' << normal << '\n' << colour << '\n';
    // std::cin.get();

    Vector half = (in + out) / (in + out).magnitude();
    double cosIn = std::abs(Vector::dotProduct(normal, in));
    double cosOut = std::abs(Vector::dotProduct(normal, out));
    double hout = std::abs(Vector::dotProduct(half, out));
    // std::cout << "cosin, cosout, hout: " << cosIn << ", " << cosOut << ", " << hout << '\n';
    
    //calculate fBaseDiffuse
    double fd90 = 0.5 + 2 * mat.roughness * hout * hout;
    // std::cout << "fd90" <<  ", " << fd90 << '\n';

    double fdIn = std::pow((1 - cosIn), 5);
    fdIn = 1 + (fd90 - 1) * fdIn;
    // std::cout << "fdin" <<  ", " << fdIn << '\n';

    double fdOut = std::pow((1 - cosOut), 5);
    fdOut = 1 + (fd90 - 1) * fdOut;
    // std::cout << "fdout" <<  ", " << fdOut << '\n';

    Colour fBaseDiffuse = colour * std::numbers::inv_pi * fdIn * fdOut * cosOut;
    // std::cout << "fBaseDiffuse" << fBaseDiffuse << '\n';
    // std::cin.get();
    
    //calculate fSubsurface
    double fss90 = mat.roughness * hout * hout;

    double fssIn = std::pow((1 - cosIn), 5);
    fssIn = 1 + (fss90 - 1) * fssIn;

    double fssOut = std::pow((1 - cosOut), 5);
    fssOut = 1 + (fss90 - 1) * fssOut;

    Colour fSubsurface = colour * 1.25 * std::numbers::inv_pi;
    double term = (1 / (cosIn + cosOut)) - 0.5;
    fSubsurface = fSubsurface * (fssIn * fssOut * term + 0.5) * cosOut;
    // std::cout << "fSubsurface" << fSubsurface << '\n';
    
    
    //calculate result
    return fBaseDiffuse * (1 - mat.subsurface) + fSubsurface * fSubsurface;
}

// * ----------------------------------------- [ DISNEY_METAL ] ------------------------------------------ * //

Colour Mat::visitor::operator()(const DisneyMetal& material) const {
    return colour;
}
