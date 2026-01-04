#include "engine/Engine.hpp"
#include "renderer/Rasterizer.hpp"
#include "renderer/RayTracer.hpp"
#include <iostream>
#include <vector>

void Engine::drawCall() {
    bitmap.clear();

    std::vector<Mesh> objects = scene.getObjects();

    // cameraRaster.rasterize(bitmap);
    cameraRayTracer.trace(bitmap);

    window.update(bitmap.getFrameBuffer());

    std::cin.get();
}