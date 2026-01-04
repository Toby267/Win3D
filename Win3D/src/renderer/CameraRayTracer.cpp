#include "renderer/CameraRayTracer.hpp"

#include "util/Matrix.hpp"
#include "renderer/Ray.hpp"
#include "scene/aabb.hpp"

// * -------------------------------------------- [ CAMERA ] -------------------------------------------- * //

Matrix CameraRayTracer::tranformationMatrix() {
    Matrix changeOfBasis = Matrix::changeOfBasis(position, direction, up);
    Matrix translation = Matrix::translate(-position.x(), -position.y(), -position.z());

    return changeOfBasis * translation;
}
Matrix CameraRayTracer::projectionMatrix() {
    return Matrix::perspective(nearFocalDistance, farFocalDistance, apperatureHeight/2, apperatureWidth/2, fieldOfView);
}
Matrix CameraRayTracer::viewportMatrix() {
    return Matrix::translate(screenWidth/2.0, screenHeight/2.0, 10000) * Matrix::scale(screenWidth/2.0, -screenHeight/2.0, 10000);
}


void CameraRayTracer::trace(std::vector<Mesh>& objects, Bitmap3D& bmap) {
    for (Mesh& obj : objects) {
        //step 0 - tesselation

        //step 1 - transform the object into world space
        obj.transform();

        //step 2 - transform the objects to camera space
        obj.applyAffineTransformation(tranformationMatrix());

        //step 3 - vertex shading
    }
    
    //these are defined in the camera
    const int cameraWidth = 1280;
    const int cameraHeight = 720;
    int focalDistance = 1000;

    int x = cameraWidth/2, y = cameraHeight/2;

    rays.clear();

    //loop through each pixel of the window
    for (int i = -cameraWidth/2; i < cameraWidth/2; i++) {
        for (int j = -cameraHeight/2; j < cameraHeight/2; j++) {
            Vector origin = Vector(0, 0, 0, 1);
            Vector direction = Vector(i, j, focalDistance, 0).normalise();
            Vector coord = Vector(i+x, cameraHeight-(j+y));
            Colour col = Colour::blue();

            rays.emplace_back(origin, direction, coord, col);
        }
    }

    // static aabb box = aabb(Vector(-50, -50, 1100), Vector(50, 50, 1200));

    for (Mesh& obj : objects) {
        // if (box.intersect(ray)) {
            // bmap.drawPixel(ray.screenCoord.x(), ray.screenCoord.y(), 1000, ray.col);
        // }

        aabb box = obj.getBBox();

        for (Ray& ray : rays) {
            if (box.intersect(ray) && obj.hit(ray)) {
                bmap.drawPixel(ray.screenCoord.x(), ray.screenCoord.y(), 1000, ray.col);
            }
        }
    }
}

// void CameraRayTracer::trace(bvhNode& scene, Bitmap3D& bmap) {
// 
// }