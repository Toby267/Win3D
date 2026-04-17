#pragma once

#include "util/Util.hpp"

// represents a single light source
class PointLight {
public:
    // original position
    Vector POSITION;
    Colour colour;

    // position used by the render for transformations
    Vector position;

    // constructors/destructor
    PointLight(Vector position, Colour colour);

    // transformations
    void applyAffineTransform(Matrix m);
    void reset();
};
