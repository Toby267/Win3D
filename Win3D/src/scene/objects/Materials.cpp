#include "scene/objects/Materials.hpp"
#include "util/Util.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numbers>

#define EXPOSURE 4

// * -------------------------------------- [ POLYMORPHISM STUFF ] --------------------------------------- * //

// evaluates the rendering equation, ignoring the Le term
Colour Mat::eval(const Material& mat, Vector in, Vector out, Vector normal, Colour normalisedMatColour, Colour normalisedlightColour) {
    Vector X{0, 0, 0}, Y{0, 0, 0};
    
    // calculate the lambert factor in the rendering equation
    double lambert = std::max(0.0, Vector::dotProduct(in, normal));
    
    // calculate the bxdf of the rendering equation
    Colour bxdf = std::visit(Mat::evaluateBxDF{in, out, normal, X, Y, normalisedMatColour}, mat);

    // calculate the reflected light in the rendering equaiton
    Colour reflected = normalisedlightColour * bxdf * lambert;
    
    // apply exposure
    Colour colour = reflected * std::pow(2, EXPOSURE); 

    // apply reinhard tone mapping, to normalise between values between [0, 1]
    colour = colour / (colour + 1);

    // denormalise to get values between [0, 255]
    colour = Colour::denormalise(colour);

    // ignore alpha stuff
    colour.a() = 255;

    return colour;
}

// * ---------------------------------------- [ MATERIALS ] ----------------------------------------- * //

Colour Mat::evaluateBxDF::operator()(const DisneyBSDF& mat) const {
    return Colour(1, 1, 1);
}

Colour Mat::evaluateBxDF::operator()(const DisneyDiffuse& mat) const {
    Vector half = in + out; half.normalise();

    double cosIn =  std::abs(Vector::dotProduct(normal, in));
    double cosOut = std::abs(Vector::dotProduct(normal, out));
    double hout   = std::abs(Vector::dotProduct(half, out));

    //calculate fBaseDiffuse
    double fd90 = 0.5 + 2 * mat.roughness * hout * hout;

    double fdIn = std::pow((1 - cosIn), 5);
    fdIn = 1 + (fd90 - 1) * fdIn;

    double fdOut = std::pow((1 - cosOut), 5);
    fdOut = 1 + (fd90 - 1) * fdOut;

    Colour fBaseDiffuse = baseColour * std::numbers::inv_pi * fdIn * fdOut * cosOut;
    
    //calculate fSubsurface
    double fss90 = mat.roughness * hout * hout;

    double fssIn = std::pow((1 - cosIn), 5);
    fssIn = 1 + (fss90 - 1) * fssIn;

    double fssOut = std::pow((1 - cosOut), 5);
    fssOut = 1 + (fss90 - 1) * fssOut;

    Colour fSubsurface = baseColour * 1.25 * std::numbers::inv_pi;
    double term = (1 / (cosIn + cosOut)) - 0.5;
    fSubsurface = fSubsurface * (fssIn * fssOut * term + 0.5) * cosOut;
    
    //calculate result
    Colour result = fBaseDiffuse * (1 - mat.subsurface) + fSubsurface * mat.subsurface;

    return result;
}

//
Colour Mat::evaluateBxDF::operator()(const DisneyMetal& mat) const {
    Vector half = in + out; half.normalise();
    
    double hout   = std::abs(Vector::dotProduct(half, out));
    double aspect = std::sqrt(1.0 - 0.9 * mat.anisotropic);
    double ax = std::max(0.0001, (mat.roughness * mat.roughness) / aspect );
    double ay = std::max(0.0001, (mat.roughness * mat.roughness) * aspect );
    
    Colour Fm = baseColour + (-baseColour + 1.0) * std::pow(1 - hout, 5);

    // Colour Dm = ...;


    


    
    
    return Colour(1, 1, 1);
}

Colour Mat::evaluateBxDF::operator()(const DisneyClearcoat& material) const {
    return Colour(1, 1, 1);
}

Colour Mat::evaluateBxDF::operator()(const DisneyGlass& material) const {
    return Colour(1, 1, 1);
}

Colour Mat::evaluateBxDF::operator()(const DisneySheen& material) const {
    return Colour(1, 1, 1);
}
