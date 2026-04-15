#include "engine/Engine.hpp"

#include "engine/Bitmap3D.hpp"
#include "engine/Window.hpp"
#include "renderer/Renderer.hpp"
#include "scene/core/Scene.hpp"
#include "settings.hpp"

Engine::Engine(int w, int h, RenderType r)
    : scene(w, h), window(w, h), bitmap(w, h), renderType(r)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//performs a dracall, drawing a frame into the bitmap
void Engine::drawCall() {
    framesRendered++;
    
    bitmap.clear();

    if (renderType == RenderType::RAY_TRACER) {
        scene.toCameraSpace();
    
        Renderer::rayTrace(bitmap, scene);
    }
    else {
        scene.toCameraSpace();
        scene.toViewportSpace();

        Renderer::rasterize(bitmap, scene);
    }

    scene.cleanup();

    window.update(bitmap.getFrameBuffer());

    #ifdef SAVE_IMAGE
    #include <string>
    bitmap.saveAsPPM("frame" + std::to_string(framesRendered) + ".ppm");
    #endif
}

void Engine::closeWindow() {
    window.close();
}
