#include "renderer/RayTracer.hpp"

#include "renderer/Ray.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

RayTracer::RayTracer(Scene& sceneRef) : scene(sceneRef) {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RayTracer::trace(Bitmap3D& bmap) {
    const Camera& camera = scene.getCam();
    const int x = camera.screenWidth/2, y = camera.screenHeight/2;

    //loop through each pixel of the window
    for (int i = -x; i < x; i++) {
        for (int j = -y; j < y; j++) {
            Ray ray = Ray(
                Vector(0, 0, 0, 1),
                Vector(i, j, camera.nearFocalDistance, 0),//.normalise(),
                Vector(i+x, camera.screenHeight-(j+y)),
                Colour::blue()
            );

            if (scene.intersect(ray)) {
                bmap.setPixel(ray.screenCoord.x(), ray.screenCoord.y(), ray.col);
            }
        }
    }
}
