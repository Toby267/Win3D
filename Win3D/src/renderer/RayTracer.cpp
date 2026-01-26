#include "renderer/Renderer.hpp"

#include "renderer/Ray.hpp"
#include "scene/objects/PointLight.hpp"
#include "scene/Scene.hpp"
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
    // std::cout << "light position: " << lights[0].position << '\n';
    const int x = camera.screenWidth/2, y = camera.screenHeight/2;

    //loop through each pixel of the window
    for (int i = -x; i < x; i++) {
        for (int j = -y; j < y; j++) {
            Ray ray = Ray(
                Vector(0, 0, 0),
                Vector(i, j, camera.nearFocalDistance).normalise()
            );

            TrianglePoint triangle;
            float t = FLOAT_MAX;
            
            //TODO: fix this such that it correctly pases the right things to the brdf and is shaded properly
            if (scene.intersect(ray, triangle, t)) {
                Colour baseColour = triangle.c0 * (1 - triangle.u - triangle.v) + triangle.c1 * triangle.u + triangle.c2 * triangle.v;
                // baseColour = baseColour * /*lights[0].colour */ lights[0].intensity;

                Vector normal = triangle.n0 * (1 - triangle.u - triangle.v) + triangle.n1 * triangle.u + triangle.n2 * triangle.v;
                Vector position = triangle.v0 * (1 - triangle.u - triangle.v) + triangle.v1 * triangle.u + triangle.v2 * triangle.v;

                // baseColour  = baseColour / 255;
                Colour finalColour = Mat::eval(triangle.mat, -ray.direction, (lights[0].position - position).normalise(), normal, baseColour); // should pass light direction, not position
                // finalColour = finalColour * 255;
                // finalColour.reNormalise();
                bmap.setPixel(i+x, camera.screenHeight-(j+y), baseColour);
            }
        }
    }
}
