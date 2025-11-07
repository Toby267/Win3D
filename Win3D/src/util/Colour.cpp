#include "util/Colour.hpp"

Colour::Colour(int r, int g, int b, int a)
    : r(r), g(g), b(b), a(a)
{}
Colour::Colour(int r, int g, int b)
    : r(r), g(g), b(b), a(255)
{}
Colour::Colour()
    : r(255), g(255), b(255), a(255)
{}

Colour Colour::operator+(const Colour& other) const {
    return Colour(
        r + other.r,
        g + other.g,
        b + other.b,
        a + other.a
    );
}
Colour Colour::operator-(const Colour& other) const {
    return Colour(
        r - other.r,
        g - other.g,
        b - other.b,
        a - other.a
    );
}
Colour Colour::operator*(const Colour& other) const {
    return Colour(
        r * other.r,
        g * other.g,
        b * other.b,
        a * other.a
    );
}
Colour Colour::operator/(const Colour& other) const {
    return Colour(
        r / other.r,
        g / other.g,
        b / other.b,
        a / other.a
    );
}

Colour Colour::operator+(const double& other) const {
    return Colour(
        r + other,
        g + other,
        g + other,
        a + other
    );
}
Colour Colour::operator-(const double& other) const {
    return Colour(
        r - other,
        g - other,
        g - other,
        a - other
    );
}
Colour Colour::operator*(const double& other) const {
    return Colour(
        r * other,
        g * other,
        g * other,
        a * other
    );
}
Colour Colour::operator/(const double& other) const {
    return Colour(
        r / other,
        g / other,
        g / other,
        a / other
    );
}

std::ostream& operator<<(std::ostream& os, const Colour& c) {
    os << "RGBA: (" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";
    return os;
}

Colour Colour::red()   { return Colour(255,   0,   0); }
Colour Colour::green() { return Colour(  0, 255,   0); }
Colour Colour::blue()  { return Colour(  0,   0, 255); }
