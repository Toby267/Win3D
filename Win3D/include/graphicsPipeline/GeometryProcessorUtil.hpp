#pragma once

#include "util/Matrix.hpp"

struct Camera {
    //position/orientation
    Vector position = Vector(0, 0, 0, 1);
    Vector direction = Vector(0, 0, 1, 0);
    Vector up = Vector(0, 1, 0, 0);

    //projection
    double apperatureWidth = 1600;
    double apperatureHeight = 900;
    
    double fieldOfView = 60.0/360.0 * 2.0*std::numbers::pi;

    //depth of field = farFocalDistance - nearFocalDistance
    double nearFocalDistance = 1000;
    double farFocalDistance = 3000;

    Camera() = default;

    Matrix tranformationMatrix();
    Matrix projectionMatrix();
};

struct Viewport {
    int screenWidth = 1280;
    int screenHeight = 720;

    Viewport() = default;

    Matrix tranformationMatrix();
};