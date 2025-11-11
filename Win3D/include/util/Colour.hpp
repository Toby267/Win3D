#pragma once

#include <ostream>
#include <sys/types.h>

struct Colour {
public:
    int r, g, b, a;

    //constructors/destructor
    Colour(int r, int g, int b, int a);
    Colour(int r, int g, int b);
    Colour();

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