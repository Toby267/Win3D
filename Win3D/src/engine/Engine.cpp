#include "engine/Engine.hpp"

void Engine::drawCall() {
    bitmap.clear();

    scene.prepare();

    // cameraRaster.rasterize(bitmap);
    cameraRayTracer.trace(bitmap);

    scene.cleanup();

    window.update(bitmap.getFrameBuffer());
}

Scene& Engine::getScene() {
    return scene;
}