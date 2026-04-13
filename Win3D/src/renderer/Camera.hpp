#pragma once

#include "util/Util.hpp"

/**
 * Contains all data related to a vritual camera.
 *
 * The camera can be in any position facing any direction, with any field of view, depth of field, and screen dimensions
 */
struct Camera {
    //position/orientation
    Vector position;
    Vector direction;
    Vector up;

    //projection
    double apperatureWidth;
    double apperatureHeight;
    
    double fieldOfView;

    //depth of field = farFocalDistance - nearFocalDistance
    double nearFocalDistance;
    double farFocalDistance;

    //viewport
    int screenWidth;
    int screenHeight;

    //methods
    Matrix tranformationMatrix() const;
    Matrix rotationMatrix() const;
    Matrix projectionMatrix() const;
    Matrix viewportMatrix() const;
} typedef Camera;
