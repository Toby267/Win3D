#include "engine/Engine.hpp"
#include <iostream>
#include <vector>

void Engine::drawCall() {
    bitmap.clear();

    std::vector<Mesh> objects = scene.getObjects();

    // cameraRaster.rasterize(objects, bitmap);
    cameraRayTracer.trace(objects, bitmap);

    window.update(bitmap.getFrameBuffer());

    std::cin.get();
}