#pragma once

#include "util/Vector.hpp"
#include "util/Colour.hpp"

struct PointLight {
    Vector position;
    Colour colour;
    float intensity;
};
