#pragma once

#include "util/Util.hpp"

// represents a single light source
struct PointLight {
private:
    // original position
    const Vector POSITION;
public:
    Vector position;
    Colour colour;

    // constructors/destructor
    PointLight(Vector position, Colour colour);

    // transformations
    void applyAffineTransform(Matrix m);
    void reset();
};
