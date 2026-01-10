#include "engine/Engine.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//performs a dracall, drawing a frame into the bitmap
void Engine::drawCall() {
    bitmap.clear();

    scene.toCameraSpace();
    cameraRayTracer.trace(bitmap);

    scene.toViewportSpace();
    // cameraRaster.rasterize(bitmap);

    scene.cleanup();

    window.update(bitmap.getFrameBuffer());
}
