#include "engine/Engine.hpp"
#include "renderer/Rasterizer.hpp"
#include "renderer/RayTracer.hpp"
#include <iostream>
#include <vector>

void Engine::drawCall() {
    bitmap.clear();

    // cameraRaster.rasterize(bitmap);
    cameraRayTracer.trace(bitmap);

    window.update(bitmap.getFrameBuffer());
}

Scene& Engine::getScene() {
    return scene;
}