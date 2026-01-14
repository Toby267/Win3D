#include "renderer/Renderer.hpp"

#include "renderer/Ray.hpp"
#include "scene/Scene.hpp"
#include "util/Colour.hpp"
#include <limits>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::rayTrace(Bitmap3D& bmap, const Scene& scene) {
    const Camera& camera = scene.getCam();
    const int x = camera.screenWidth/2, y = camera.screenHeight/2;

    //loop through each pixel of the window
    for (int i = -x; i < x; i++) {
        for (int j = -y; j < y; j++) {
            Ray ray = Ray(
                Vector(0, 0, 0, 1),
                Vector(i, j, camera.nearFocalDistance, 0),//.normalise(),
                Colour::blue()
            );

            if (scene.intersect(ray)) {
                bmap.setPixel(i+x, camera.screenHeight-(j+y), ray.col);
            }

        }
    }
}
