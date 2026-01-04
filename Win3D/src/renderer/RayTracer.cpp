#include "renderer/RayTracer.hpp"

#include "renderer/Ray.hpp"
#include "scene/aabb.hpp"
#include <vector>

RayTracer::RayTracer(Scene& sceneRef) : scene(sceneRef) {

}

void RayTracer::trace(Bitmap3D& bmap) {
    rays.clear();

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
    
    for (Mesh* object : objects) {
        Mesh obj = *object;
        
        //step 1 - transform the object into world space
        obj.transform();

        //step 2 - transform the objects to camera space
        obj.applyAffineTransformation(camera.tranformationMatrix());

        //step 3 - ray trace
        aabb box = obj.getBBox();
        for (Ray& ray : rays) {
            if (box.intersect(ray) && obj.hit(ray)) {
                bmap.drawPixel(ray.screenCoord.x(), ray.screenCoord.y(), 1000, ray.col);
            }
        }
    }
}
