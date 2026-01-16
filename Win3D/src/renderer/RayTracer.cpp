#include "renderer/Renderer.hpp"

#include "renderer/Ray.hpp"
#include "scene/PointLight.hpp"
#include "scene/Scene.hpp"
#include "util/Colour.hpp"
#include "util/Vector.hpp"
#include <iostream>
#include <limits>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::rayTrace(Bitmap3D& bmap, const Scene& scene) {
    constexpr float FLOAT_MAX = std::numeric_limits<float>::max();
    
    const Camera& camera = scene.getCam();
    const std::vector<PointLight> lights = scene.getLights();
    std::cout << "light position: " << lights[0].position << '\n';
    const int x = camera.screenWidth/2, y = camera.screenHeight/2;

    //loop through each pixel of the window
    for (int i = -x; i < x; i++) {
        for (int j = -y; j < y; j++) {
            Ray ray = Ray(
                Vector(0, 0, 0),
                Vector(i, j, camera.nearFocalDistance)//.normalise()
            );

            TrianglePoint triangle;
            float t = FLOAT_MAX;
            
            //TODO: fix this such that it correctly pases the right things to the brdf and is shaded properly
            if (scene.intersect(ray, triangle, t)) {
                Colour baseColour = triangle.c0 * (1 - triangle.u - triangle.v) + triangle.c1 * triangle.u + triangle.c2 * triangle.v;
                // baseColour = lights[0].colour * lights[0].intensity * baseColour;
                std::cout << "baseColour: " << baseColour << '\n';

                Vector normal = triangle.n0 * (1 - triangle.u - triangle.v) + triangle.n1 * triangle.u + triangle.n2 * triangle.v;
                Vector position = triangle.v0 * (1 - triangle.u - triangle.v) + triangle.v1 * triangle.u + triangle.v2 * triangle.v;
                std::cout << "triangle position:\n";
                std::cout << triangle.v0 << ", " << triangle.v1 << ", " << triangle.v2 << '\n' << '\n';

                Colour finalColour = Mat::eval(triangle.mat, -ray.direction, -(lights[0].position - position), normal, baseColour); // should pass light direction, not position
                std::cout << "colour: " << finalColour << '\n';
                bmap.setPixel(i+x, camera.screenHeight-(j+y), baseColour);
            }
        }
    }
}
