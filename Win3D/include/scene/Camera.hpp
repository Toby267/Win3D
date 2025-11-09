#pragma once

#include "util/Matrix.hpp"
#include "util/Vector.hpp"

class Camera {
private:
    Matrix projection;
    Vector position;
    Vector direction;
    int d;

public:
    //constructors/destructor
    Camera();
    Camera(Matrix projection, Vector position, Vector direction, int d);

    //getters/setters
    Matrix getProjection();
};