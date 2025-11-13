#pragma once

#include "util/Matrix.hpp"

struct transformation {

};

struct Camera {
    Vector position     = Vector(0, 0, 0, 1);
    Vector direction    = Vector(0, 0, 1, 0);
    Vector up           = Vector(0, 1, 0, 0);

    Matrix transformation{4, 4};

    void calcTransformationMatrix();
};

struct Projection {
    double lensWidth  = 1600;
    double lensHeight = 900;
    
    double depthOfField = 2000;
    // double fieldOfView  = 90;

    Matrix transformation{4, 4};

    // enum type {orthographic, perspctive} projection;

    void calcTransformationMatrix();
};

struct Viewport {
    int screenWidth = 1280;
    int screenHeight = 720;

    Matrix transformation{4, 4};

    void calcTransformationMatrix();
};