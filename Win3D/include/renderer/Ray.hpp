#pragma once

#include "util/Colour.hpp"
#include "util/Vector.hpp"

struct Ray {
    Vector origin;
    Vector direction;

    Vector screenCoord;
    Colour col;
} typedef Ray;