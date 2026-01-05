#include "engine/Engine.hpp"

void Engine::drawCall() {
    bitmap.clear();

    // cameraRaster.rasterize(bitmap);
    cameraRayTracer.trace(bitmap);

    window.update(bitmap.getFrameBuffer());
}

Scene& Engine::getScene() {
    return scene;
}