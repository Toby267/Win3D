#include "scene/Materials.hpp"
#include "util/Colour.hpp"
#include "util/Vector.hpp"
#include <cmath>
#include <cstdlib>
#include <numbers>

DisneyDiffuse::DisneyDiffuse(Colour c, double r, double s)
    : baseColour(c), roughness(r), subsurface(s)
{ }

Colour visitor::operator()(const DisneyDiffuse& mat) const {
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

    Colour fBaseDiffuse = mat.baseColour * std::numbers::inv_pi * fdIn * fdOut * cosOut;
    
    //calculate fSubsurface
    double fss90 = mat.roughness * hout * hout;

    double fssIn = std::pow((1 - cosIn), 5);
    fssIn = 1 + (fss90 - 1) * fssIn;

    double fssOut = std::pow((1 - cosOut), 5);
    fssOut = 1 + (fss90 - 1) * fssOut;

    Colour fSubsurface = mat.baseColour * 1.25 * std::numbers::inv_pi;
    double term = (1 / (cosIn + cosOut)) - 0.5;
    fSubsurface = fSubsurface * (fssIn * fssOut * term + 0.5) * cosOut;
    
    //calculate result
    return fBaseDiffuse * (1 - mat.subsurface) + fSubsurface * fSubsurface;
}

Colour visitor::operator()(const DisneyMetal& material) const {
    return Colour::red();
}

Colour eval(const Material& mat, Vector& in, Vector& out, Vector& normal) {
    return std::visit(visitor{in, out, normal}, mat);
}
