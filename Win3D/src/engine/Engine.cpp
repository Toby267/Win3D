#include "engine/Engine.hpp"

void Engine::drawCall(std::vector<Object> objects) {
    bitmap.clear();

    // cameraRaster.rasterize(objects, bitmap);
    cameraRayTracer.trace(objects, bitmap);

    window.update(bitmap.getFrameBuffer());
}