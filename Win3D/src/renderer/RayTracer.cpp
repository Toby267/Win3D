#include "renderer/Renderer.hpp"

#include "renderer/Ray.hpp"
#include "scene/PointLight.hpp"
#include "scene/Scene.hpp"
#include "util/Colour.hpp"
#include <limits>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::rayTrace(Bitmap3D& bmap, const Scene& scene) {
    constexpr float FLOAT_MAX = std::numeric_limits<float>::max();
    
    const Camera& camera = scene.getCam();
    const std::vector<PointLight> lights = scene.getLights();
    const int x = camera.screenWidth/2, y = camera.screenHeight/2;

    //loop through each pixel of the window
    for (int i = -x; i < x; i++) {
        for (int j = -y; j < y; j++) {
            Ray ray = Ray(
                Vector(0, 0, 0, 1),
                Vector(i, j, camera.nearFocalDistance, 0)//.normalise(),
            );

            HitRecord rec(FLOAT_MAX);

            if (scene.intersect(ray, rec)) {
                Colour colour = Mat::eval(rec.m, lights[0].position, -ray.direction, Vector{}, rec.c0, rec.c1, rec.c2, rec.u, rec.v);
                bmap.setPixel(i+x, camera.screenHeight-(j+y), colour);
            }
        }
    }
}
