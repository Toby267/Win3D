#pragma once

#include "util/Matrix.hpp"

struct Camera {
    Vector position;
    Vector direction;
    Vector up;

    Camera() = default;
    Camera(Vector position, Vector direction, Vector up);

    Matrix getTransformationMatrix();
};

struct Projection {
    double apperatureWidth;
    double apperatureHeight;
    
    double fieldOfView;

    double nearFocalDistance;
    double farFocalDistance;

    // enum type {orthographic, perspctive} projection;

    Projection() = default;
    Projection(double apperatureWidth, double apperatureHeight, double depthOfField, double fieldOfView, double focalDistance);

    Matrix getTransformationMatrix();
};

struct Viewport {
    int screenWidth;
    int screenHeight;

    Viewport() = default;
    Viewport(int screenWidth, int screenHeight);

    Matrix getTransformationMatrix();
};