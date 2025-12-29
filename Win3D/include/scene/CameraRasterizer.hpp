#pragma once

#include "util/Matrix.hpp"
#include "renderer/Bitmap3D.hpp"
#include "scene/Object.hpp"

class CameraRasterizer {
private:
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

public:
    CameraRasterizer() = default;

    Matrix tranformationMatrix();
    Matrix projectionMatrix();

    Bitmap3D rasterize(std::vector<Object>& objects);

private:
    //private methods
    void drawTriangle(Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3);
    void drawLine(Vector start, Vector end, Colour c1, Colour c2);
};

// struct Viewport {
//     int screenWidth = 1280;
//     int screenHeight = 720;

//     Viewport() = default;

//     Matrix tranformationMatrix();
// };