#pragma once

#include <sys/types.h>

struct Colour {
    u_int8_t r, g, b, a;

    Colour(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);
    Colour(u_int8_t r, u_int8_t g, u_int8_t b);
    Colour();
};