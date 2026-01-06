#include "renderer/RayTracer.hpp"

#include "renderer/Ray.hpp"
#include <vector>

RayTracer::RayTracer(Scene& sceneRef) : scene(sceneRef) {

}

void RayTracer::trace(Bitmap3D& bmap) {
    Camera& camera = scene.getCam();
    std::vector<Mesh*>& objects = scene.getObjects();
    
    int x = camera.screenWidth/2, y = camera.screenHeight/2;
    
    //loop through each pixel of the window
    for (int i = -camera.screenWidth/2; i < camera.screenWidth/2; i++) {
        for (int j = -camera.screenHeight/2; j < camera.screenHeight/2; j++) {
            Vector origin = Vector(0, 0, 0, 1);
            Vector direction = Vector(i, j, camera.nearFocalDistance, 0).normalise();
            Vector coord = Vector(i+x, camera.screenHeight-(j+y));
            Colour col = Colour::blue();

            rays.emplace_back(origin, direction, coord, col);
        }
    }

    for (Ray& ray : rays) {
        if (scene.intersect(ray)) {
            bmap.drawPixel(ray.screenCoord.x(), ray.screenCoord.y(), 1000, ray.col);
        }
    }

    rays.clear();
}
