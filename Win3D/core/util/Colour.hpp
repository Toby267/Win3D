#pragma once

#include "Vector.hpp"

#include <ostream>

class Colour {
private:
    Vector data;
public:
    //constructors/destructor
    Colour();
    Colour(int red, int green, int blue, int alpha);
    Colour(int red, int green, int blue);

    //getters/setters
    double& r();
    double& g();
    double& b();
    double& a();

    const double& r() const;
    const double& g() const;
    const double& b() const;
    const double& a() const;

    //public methods
    void reNormalise();

    //operator overloads
    Colour operator+(const Colour& other) const;
    Colour operator-(const Colour& other) const;
    Colour operator*(const Colour& other) const;
    Colour operator/(const Colour& other) const;
    
    Colour operator+(double other) const;
    Colour operator-(double other) const;
    Colour operator*(double other) const;
    Colour operator/(double other) const;

    friend std::ostream& operator<<(std::ostream& os, const Colour& colour);

    //static methods
    static Colour red(), green(), blue(), cyan(), magenta(), yellow();
};