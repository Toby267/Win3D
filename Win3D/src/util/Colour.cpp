#include "util/Util.hpp"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Colour::Colour(double red, double green, double blue, double alpha)
    : data(red, green, blue, alpha)
{

}
Colour::Colour(double red, double green, double blue)
    : data(red, green, blue, 255)
{

}
Colour::Colour()
    : data(255, 255, 255, 255)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


double& Colour::r() {
    return data.x();
}
double& Colour::g() {
    return data.y();
}
double& Colour::b() {
    return data.z();
}
double& Colour::a() {
    return data.w();
}

const double& Colour::r() const {
    return data.x();
}
const double& Colour::g() const {
    return data.y();
}
const double& Colour::b() const {
    return data.z();
}
const double& Colour::a() const {
    return data.w();
}

Colour Colour::normalise(Colour c) {
    return Colour(
        c.data.x() / 255,
        c.data.y() / 255,
        c.data.z() / 255,
        c.data.w() / 255
    );
}
Colour Colour::denormalise(Colour c) {
    return Colour(
        c.data.x() * 255,
        c.data.y() * 255,
        c.data.z() * 255,
        c.data.w() * 255
    );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * --------------------------------------- [ OPERATOR OVERLOADS ] -------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Colour Colour::operator+(const Colour& other) const {
    return Colour(
        r() + other.r(),
        g() + other.g(),
        b() + other.b(),
        a() + other.a()
    );
}
Colour Colour::operator-(const Colour& other) const {
    return Colour(
        r() - other.r(),
        g() - other.g(),
        b() - other.b(),
        a() - other.a()
    );
}
Colour Colour::operator*(const Colour& other) const {
    return Colour(
        r() * other.r(),
        g() * other.g(),
        b() * other.b(),
        a() * other.a()
    );
}
Colour Colour::operator/(const Colour& other) const {
    // std::cout << "r, g, b, a: " << r() << ", " << g() << ", " << b() << ", " << a() << "\n";
    // std::cout << "other.r, other.g, other.b, other.a: " << other.r() << ", " << other.g() << ", " << other.b() << ", " << other.a() << "\n";
    // std::cout << "division: " << r() / other.r() << ", " << g() / other.g() << ", " << b() / other.b() << ", " << a() / other.a() << "\n";
    
    Colour c(
        r() / other.r(),
        g() / other.g(),
        b() / other.b(),
        a() / other.a()
    );

    // std::cout << "c: " << c << '\n';
    return c;
}

Colour Colour::operator+(double other) const {
    return Colour(
        r() + other,
        g() + other,
        b() + other,
        a() + other
    );
}
Colour Colour::operator-(double other) const {
    return Colour(
        r() - other,
        g() - other,
        b() - other,
        a() - other
    );
}
Colour Colour::operator*(double other) const {
    return Colour(
        r() * other,
        g() * other,
        b() * other,
        a() * other
    );
}
Colour Colour::operator/(double other) const {
    return Colour(
        r() / other,
        g() / other,
        b() / other,
        a() / other
    );
}

Colour Colour::operator-() const {
    return Colour(
        -r(),
        -g(),
        -b(),
        -a()
    );
}

std::ostream& operator<<(std::ostream& os, const Colour& colour) {
    os << "RGBA: (" << colour.r() << ", " << colour.g() << ", " << colour.b() << ", " << colour.a() << ")";
    return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ STATIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Colour Colour::white()   { return Colour(255, 255, 255); }
Colour Colour::red()     { return Colour(255,   0,   0); }
Colour Colour::green()   { return Colour(  0, 255,   0); }
Colour Colour::blue()    { return Colour(  0,   0, 255); }
Colour Colour::cyan()    { return Colour(  0, 255, 255); }
Colour Colour::magenta() { return Colour(255,   0, 255); }
Colour Colour::yellow()  { return Colour(255, 255,   0); }
