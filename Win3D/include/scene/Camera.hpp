#pragma once

#include "util/Matrix.hpp"
#include "util/Vector.hpp"

class Camera {
private:
    Matrix projection = Matrix::orthographic(0, 0, 0, 1280, 720, 1000);
    Vector position = Vector(0, 0, 0, 1);
    Vector direction = Vector(0, 0, -1, 0);
    int d = 1;

public:
    //constructors/destructor
    Camera();

    //getters/setters
    Matrix getProjection();
};