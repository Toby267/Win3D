#include "renderer/Renderer.hpp"

#include "renderer/Ray.hpp"
#include "scene/objects/PointLight.hpp"
#include "scene/core/Scene.hpp"
#include "util/Util.hpp"
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
                Vector(0, 0, 0),
                Vector(i, j, camera.nearFocalDistance).normalise()
            );

            HitRecord record;
            record.t = FLOAT_MAX;
            scene.intersect(ray, record);

            if (record.t != FLOAT_MAX) {
                Colour baseColour = record.c0 * (1 - record.u - record.v) + record.c1 * record.u + record.c2 * record.v;
                Vector normal = record.n0 * (1 - record.u - record.v) + record.n1 * record.u + record.n2 * record.v;
                Vector position = record.v0 * (1 - record.u - record.v) + record.v1 * record.u + record.v2 * record.v;
                Colour finalColour = Mat::eval(record.mat, -ray.direction, (lights[0].position - position).normalise(), normal, baseColour); // should pass light direction, not position
                bmap.setPixel(i+x, camera.screenHeight-(j+y), baseColour);
            }
        }
    }
}
