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
    double lensWidth;
    double lensHeight;
    
    double depthOfField;
    double fieldOfView;

    double near;

    // enum type {orthographic, perspctive} projection;

    Projection() = default;
    Projection(double lensWidth, double lensHeight, double depthOfField, double fieldOfView, double near);

    Matrix getTransformationMatrix();
};

struct Viewport {
    int screenWidth;
    int screenHeight;

    Viewport() = default;
    Viewport(int screenWidth, int screenHeight);

    Matrix getTransformationMatrix();
};