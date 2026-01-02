#include "engine/Engine.hpp"
#include "renderer/objects/bvhNode.hpp"
#include <iostream>

void Engine::drawCall(std::vector<Mesh> objects) {
    bitmap.clear();

    // bvhNode tree = bvhNode(objects);

    // cameraRaster.rasterize(objects, bitmap);
    cameraRayTracer.trace(objects, bitmap);
    // cameraRayTracer.trace(tree, bitmap);

    window.update(bitmap.getFrameBuffer());

    std::cin.get();
}