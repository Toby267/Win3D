#include "util/Colour.hpp"

Colour::Colour(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a)
    : r(r), g(g), b(b), a(a)
{}
Colour::Colour(u_int8_t r, u_int8_t g, u_int8_t b)
    : r(r), g(g), b(b), a(255)
{}
Colour::Colour()
    : r(255), g(255), b(255), a(255)
{}