#include "scene/objects/PointLight.hpp"
#include "util/Util.hpp"

// constructor
PointLight::PointLight(Vector p, Colour c)
    : position(p), colour(c) {}

// applys an affine transformation to the light
void PointLight::applyAffineTransform(Matrix m) {
    position = Matrix::asMat3(m) * position;
}

// resets the light to its original position
void PointLight::reset() {
    position = POSITION;
}
