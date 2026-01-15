#include "scene/Materials.hpp"
#include "util/Colour.hpp"
#include "util/Vector.hpp"
#include <cmath>
#include <cstdlib>
#include <numbers>

Mat::DisneyDiffuse::DisneyDiffuse(double r, double s)
    : roughness(r), subsurface(s)
{ }

Colour Mat::visitor::operator()(const DisneyDiffuse& mat) const {
    return colour;

    Vector half = in + out / (in + out).magnitude();
    double cosIn = std::abs(Vector::dotProduct(normal, in));
    double cosOut = std::abs(Vector::dotProduct(normal, out));
    double hout = std::abs(Vector::dotProduct(half, out));
    
    //calculate fBaseDiffuse
    double fd90 = 0.5 + 2 * mat.roughness * hout * hout;

    double fdIn = std::pow((1 - cosIn), 5);
    fdIn = 1 + (fd90 - 1) * fdIn;

    double fdOut = std::pow((1 - cosOut), 5);
    fdOut = 1 + (fd90 - 1) * fdOut;

    Colour fBaseDiffuse = colour * std::numbers::inv_pi * fdIn * fdOut * cosOut;
    
    //calculate fSubsurface
    double fss90 = mat.roughness * hout * hout;

    double fssIn = std::pow((1 - cosIn), 5);
    fssIn = 1 + (fss90 - 1) * fssIn;

    double fssOut = std::pow((1 - cosOut), 5);
    fssOut = 1 + (fss90 - 1) * fssOut;

    Colour fSubsurface = colour * 1.25 * std::numbers::inv_pi;
    double term = (1 / (cosIn + cosOut)) - 0.5;
    fSubsurface = fSubsurface * (fssIn * fssOut * term + 0.5) * cosOut;
    
    //calculate result
    return fBaseDiffuse * (1 - mat.subsurface) + fSubsurface * fSubsurface;
}

Colour Mat::visitor::operator()(const DisneyMetal& material) const {
    return colour;
}

Colour Mat::eval(const Mat::Material& mat, Vector in, Vector out, Vector normal, Colour c0, Colour c1, Colour c2, float u, float v) {
    Colour c = c0 * (1 - u - v) + c1 * u + c2 * v;
    return std::visit(Mat::visitor{in, out, normal, c}, mat);
}
