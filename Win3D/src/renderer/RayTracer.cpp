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
    constexpr double DOUBLE_MAX = std::numeric_limits<double>::max();
    
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
            record.t = DOUBLE_MAX;
            scene.intersect(ray, record);

            if (record.t != DOUBLE_MAX) {
                double w = 1 - record.u - record.v;
                
                Vector position = record.v0 * w + record.v1 * record.u + record.v2 * record.v;
                Vector normal   = record.n0 * w + record.n1 * record.u + record.n2 * record.v;
                Colour matColour   = record.c0 * w + record.c1 * record.u + record.c2 * record.v;
                Colour lightColour = lights[0].colour;

                matColour = Colour::normalise(matColour);
                lightColour = Colour::normalise(lightColour);
                
                Vector in = (lights[0].position - position).normalise();
                Vector out = -ray.direction;
                normal.normalise();

                Colour finalColour = Mat::eval(record.mat, in, out, normal.normalise(), matColour, lightColour);
                bmap.setPixel(i+x, camera.screenHeight-(j+y), finalColour);
            }
        }
    }
}
