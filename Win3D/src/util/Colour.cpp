#include "util/Colour.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Colour::Colour(int r, int g, int b, int a)
    : vect(r, g, b, a)
{

}
Colour::Colour(int r, int g, int b)
    : vect(r, g, b, 255)
{

}
Colour::Colour()
    : vect(255, 255, 255, 255)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


double& Colour::r() {
    return vect.x();
}
double& Colour::g() {
    return vect.y();
}
double& Colour::b() {
    return vect.z();
}
double& Colour::a() {
    return vect.w();
}

const double& Colour::r() const {
    return vect.x();
}
const double& Colour::g() const {
    return vect.y();
}
const double& Colour::b() const {
    return vect.z();
}
const double& Colour::a() const {
    return vect.w();
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
        g() + other,
        a() + other
    );
}
Colour Colour::operator-(double other) const {
    return Colour(
        r() - other,
        g() - other,
        g() - other,
        a() - other
    );
}
Colour Colour::operator*(double other) const {
    return Colour(
        r() * other,
        g() * other,
        g() * other,
        a() * other
    );
}
Colour Colour::operator/(double other) const {
    return Colour(
        r() / other,
        g() / other,
        g() / other,
        a() / other
    );
}

std::ostream& operator<<(std::ostream& os, const Colour& c) {
    os << "RGBA: (" << c.r() << ", " << c.g() << ", " << c.b() << ", " << c.a() << ")";
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
