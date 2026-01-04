#pragma once

#include "scene/bvhNode.hpp"
#include "util/Matrix.hpp"
#include "engine/Bitmap3D.hpp"
#include "scene/Mesh.hpp"
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
    
    //to make is so that this is used, you need to offset the camera origin when generating the rays, or just change the angle of them
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

    void trace(std::vector<Mesh>& objects, Bitmap3D& bmap);
    // void trace(bvhNode& scene, Bitmap3D& bmap);
};
