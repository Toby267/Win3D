#pragma once

#include "util/Matrix.hpp"
#include "engine/Bitmap3D.hpp"
#include "renderer/Object.hpp"
#include "renderer/Ray.hpp"

class CameraRayTracer {
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

    //viewport
    int screenWidth = 1280;
    int screenHeight = 720;

    std::vector<Ray> rays = std::vector<Ray>();

public:
    Matrix tranformationMatrix();
    Matrix projectionMatrix();
    Matrix viewportMatrix();

    void trace(std::vector<Object>& objects, Bitmap3D& bmap);

private:
    float mollerTrumboreIntersection(Vector orig, Vector dir, Vector vert0, Vector vert1, Vector vert2);
};
