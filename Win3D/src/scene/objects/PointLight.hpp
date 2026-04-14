#pragma once

#include "util/Util.hpp"

// represents a light source
struct PointLight {
private:
    const Vector POSITION;
public:
    Vector position;
    Colour colour;

    // constructors
    PointLight(Vector position, Colour colour);

    // transformations
    void applyAffineTransform(Matrix m);
    void reset();
};
