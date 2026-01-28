#include "renderer/Renderer.hpp"

#include "renderer/Ray.hpp"
#include "scene/objects/PointLight.hpp"
#include "scene/core/Scene.hpp"
#include "util/Util.hpp"
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::rayTrace(Bitmap3D& bmap, const Scene& scene) {
    constexpr float FLOAT_MAX = std::numeric_limits<float>::max();
    
    const Camera& camera = scene.getCam();
    const std::vector<PointLight> lights = scene.getLights();
    // std::cout << "light position: " << lights[0].position << '\n';
    const int x = camera.screenWidth/2, y = camera.screenHeight/2;

    //loop through each pixel of the window
    for (int i = -x; i < x; i++) {
        for (int j = -y; j < y; j++) {
            Ray ray = Ray(
                Vector(0, 0, 0),
                Vector(i, j, camera.nearFocalDistance).normalise()
            );

            // TrianglePoint triangle;
            // float t = FLOAT_MAX;
            HitRecord record;
            record.t = FLOAT_MAX;

            // std::cout << "before intersection" << '\n';
            scene.intersect(ray, record);
            // std::cout << "after intersection" << '\n';

            if (record.t != FLOAT_MAX) {
                // std::cout << "is intersection enter" << '\n';
                Colour baseColour = record.v1.colour * (1 - record.u - record.v) * record.v2.colour * record.u * record.v3.colour * record.v;
                Vector normal = record.v1.normal * (1 - record.u - record.v) * record.v2.normal * record.u * record.v3.normal * record.v;
                Vector position = record.v1.position * (1 - record.u - record.v) * record.v2.position * record.u * record.v3.position * record.v;
                // Colour finalColour = Mat::eval();
                bmap.setPixel(i+x, camera.screenHeight-(j+y), baseColour);
                // std::cout << "is intersection exit" << '\n';
            }
            
            //TODO: fix this such that it correctly pases the right things to the brdf and is shaded properly
            
            // if (scene.intersect(ray, triangle, t)) {
                // Colour baseColour = triangle.c0 * (1 - triangle.u - triangle.v) + triangle.c1 * triangle.u + triangle.c2 * triangle.v;
                // baseColour = baseColour * /*lights[0].colour */ lights[0].intensity;

                // Vector normal = triangle.n0 * (1 - triangle.u - triangle.v) + triangle.n1 * triangle.u + triangle.n2 * triangle.v;
                // Vector position = triangle.v0 * (1 - triangle.u - triangle.v) + triangle.v1 * triangle.u + triangle.v2 * triangle.v;

                // baseColour  = baseColour / 255;
                // Colour finalColour = Mat::eval(triangle.mat, -ray.direction, (lights[0].position - position).normalise(), normal, baseColour); // should pass light direction, not position
                // finalColour = finalColour * 255;
                // finalColour.reNormalise();
                // bmap.setPixel(i+x, camera.screenHeight-(j+y), baseColour);
            // }
            
        }
    }
}
