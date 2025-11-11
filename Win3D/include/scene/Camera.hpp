#pragma once

#include "util/Matrix.hpp"
#include "util/Vector.hpp"

class Camera {
private:
    Matrix projection = Matrix::perspective(-640, -360, -500, 640, 360, 500);

    Vector position     = Vector(0, 0, 0, 1);
    Vector direction    = Vector(0, 0, 1, 0);
    Vector up           = Vector(0, 1, 0, 0);

    int d = 1;

public:
    //constructors/destructor
    Camera() {};

    //getters/setters
    Matrix getProjection() const;
    Matrix getTransformation() const;
};