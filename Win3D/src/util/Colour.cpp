#include "util/Colour.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Colour::Colour(int red, int green, int blue, int alpha)
    : data(red, green, blue, alpha)
{

}
Colour::Colour(int red, int green, int blue)
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
    return Colour(
        r() / other.r(),
        g() / other.g(),
        b() / other.b(),
        a() / other.a()
    );
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

std::ostream& operator<<(std::ostream& os, const Colour& colour) {
    os << "RGBA: (" << colour.r() << ", " << colour.g() << ", " << colour.b() << ", " << colour.a() << ")";
    return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ STATIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Colour Colour::red()     { return Colour(255,   0,   0); }
Colour Colour::green()   { return Colour(  0, 255,   0); }
Colour Colour::blue()    { return Colour(  0,   0, 255); }
Colour Colour::cyan()    { return Colour(  0, 255, 255); }
Colour Colour::magenta() { return Colour(255,   0, 255); }
Colour Colour::yellow()  { return Colour(255, 255,   0); }
