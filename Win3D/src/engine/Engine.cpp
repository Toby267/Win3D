#include "engine/Engine.hpp"

#include "engine/Bitmap3D.hpp"
#include "engine/Window.hpp"
#include "renderer/Renderer.hpp"
#include "scene/core/Scene.hpp"

Engine::Engine(int w, int h, RenderType r)
    : scene(w, h), window(w, h), bitmap(w, h), renderType(r)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//performs a dracall, drawing a frame into the bitmap
void Engine::drawCall() {
    bitmap.clear();

    if (renderType == RenderType::RASTERIZER) {
        scene.toCameraSpace();
        scene.toViewportSpace();

        Renderer::rasterize(bitmap, scene);
    }
    else {
        scene.toCameraSpace();
    
        Renderer::rayTrace(bitmap, scene);
    }

    scene.cleanup();

    window.update(bitmap.getFrameBuffer());
}
