#pragma once

#include <ostream>
#include <sys/types.h>

struct Colour {
    int r, g, b, a;

    Colour(int r, int g, int b, int a);
    Colour(int r, int g, int b);
    Colour();

    Colour operator+(const Colour& other) const;
    Colour operator-(const Colour& other) const;
    Colour operator*(const Colour& other) const;
    Colour operator/(const Colour& other) const;
    
    Colour operator+(const double& other) const;
    Colour operator-(const double& other) const;
    Colour operator*(const double& other) const;
    Colour operator/(const double& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Colour& c);
};