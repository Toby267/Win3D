#include "scene/Materials.hpp"
#include "util/Colour.hpp"
#include "util/Vector.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numbers>

DisneyDiffuse::DisneyDiffuse(Colour c, double r, double s)
    : baseColour(c), roughness(r), subsurface(s)
{ }



Colour visitor::operator()(const DisneyDiffuse& material) const {
    // std::cout << "eval2\n";
    return Colour::red();
}
Colour visitor::operator()(const DisneyMetal& material) const {
    // std::cout << "eval2\n";
    return Colour::red();
}


Colour DisneyMetal::evaluate(Vector in, Vector out, Vector normal) const {
    // std::cout << "eval1\n";
    return Colour::red();
}
Colour DisneyDiffuse::evaluate(Vector in, Vector out, Vector normal) const {
    // std::cout << "eval1\n";
    return Colour::red();
}


Colour eval1(const Material& mat, Vector& in, Vector& out, Vector& normal) {
    return std::visit([in, out, normal](const auto& item){
        return item.evaluate(in, out, normal);
    }, mat);
}

Colour eval2(const Material& mat, Vector& in, Vector& out, Vector& normal) {
    return std::visit(visitor{in, out, normal}, mat);
}















/*
    Vector half = in + out / (in + out).magnitude();
    double cosIn = std::abs(Vector::dotProduct(normal, in));
    double cosOut = std::abs(Vector::dotProduct(normal, out));
    double hout = std::abs(Vector::dotProduct(half, out));

    //calculate fBaseDiffuse
    double fd90 = 0.5 + 2 * roughness * hout * hout;

    double fdIn = std::pow((1 - cosIn), 5);
    fdIn = 1 + (fd90 - 1) * fdIn;

    double fdOut = std::pow((1 - cosOut), 5);
    fdOut = 1 + (fd90 - 1) * fdOut;

    Colour fBaseDiffuse = baseColour * std::numbers::inv_pi * fdIn * fdOut * cosOut;

    //calculate fSubsurface
    double fss90 = roughness * hout * hout;

    double fssIn = std::pow((1 - cosIn), 5);
    fssIn = 1 + (fss90 - 1) * fssIn;

    double fssOut = std::pow((1 - cosOut), 5);
    fssOut = 1 + (fss90 - 1) * fssOut;

    Colour fSubsurface = baseColour * 1.25 * std::numbers::inv_pi;
    double term = (1 / (cosIn + cosOut)) - 0.5;
    fSubsurface = fSubsurface * (fssIn * fssOut * term + 0.5) * cosOut;

    //calculate
    return fBaseDiffuse * (1 - subsurface) + fSubsurface * fSubsurface;
*/