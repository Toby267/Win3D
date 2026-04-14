#include "renderer/Renderer.hpp"

#include "renderer/Ray.hpp"
#include "scene/objects/Materials.hpp"
#include "scene/objects/PointLight.hpp"
#include "scene/core/Scene.hpp"
#include "util/Util.hpp"
#include <iostream>
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
    const int total = camera.screenWidth * camera.screenHeight;
    int progress = 0;

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
                
                Vector position    = record.v0     * w + record.v1     * record.u + record.v2     * record.v;
                Vector normal      = record.n0     * w + record.n1     * record.u + record.n2     * record.v;
                Colour matColour   = record.c0     * w + record.c1     * record.u + record.c2     * record.v;
                
                matColour = Colour::normalise(matColour);
                normal.normalise();

                Vector out = -ray.direction;

                Vector arbitraryLine = normal.x() < 0.9 ? Vector{1, 0, 0} : Vector{0, 1, 0};
                Vector X = Vector::crossProduct(arbitraryLine, normal).normalise();
                Vector Y = Vector::crossProduct(normal, X).normalise();

                Colour finalColour = Mat::evaluateLights(record.mat, out, normal, X, Y, matColour, position, lights);

                bmap.setPixel(i+x, camera.screenHeight-(j+y), finalColour);
            }

            progress++;
            if (progress % 10000 == 0) {
                double percentage = ((double)progress * 100) / (double)total;
                std::cout << percentage << "%" << " done" << '\n';
            }
        }
    }
}
