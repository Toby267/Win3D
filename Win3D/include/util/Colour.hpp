#pragma once

#include "Vector.hpp"

#include <ostream>

struct Colour {
private:
    Vector vect;
public:
    //constructors/destructor
    Colour();
    Colour(int r, int g, int b, int a);
    Colour(int r, int g, int b);

    //getters/setters
    double& r();
    double& g();
    double& b();
    double& a();

    const double& r() const;
    const double& g() const;
    const double& b() const;
    const double& a() const;

    //operator overloads
    Colour operator+(const Colour& other) const;
    Colour operator-(const Colour& other) const;
    Colour operator*(const Colour& other) const;
    Colour operator/(const Colour& other) const;
    
    Colour operator+(double other) const;
    Colour operator-(double other) const;
    Colour operator*(double other) const;
    Colour operator/(double other) const;

    friend std::ostream& operator<<(std::ostream& os, const Colour& c);

    //static methods
    static Colour red(), green(), blue(), cyan(), magenta(), yellow();
};