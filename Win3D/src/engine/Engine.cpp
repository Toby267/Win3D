#include "engine/Engine.hpp"

void Engine::drawCall(std::vector<Object> objects) {
    // drawCallRaster(objects);
    // drawCallRayTraced(objects);

    bitmap.clear();

    // cameraRaster.rasterize(objects, bitmap);
    cameraRayTracer.trace(objects, bitmap);

    window.update(bitmap.getFrameBuffer());
}