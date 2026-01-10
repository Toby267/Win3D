#include "engine/Engine.hpp"

#include "engine/Bitmap3D.hpp"
#include "engine/Window.hpp"
#include "renderer/Renderer.hpp"
#include "scene/Scene.hpp"

Engine::Engine(int width, int height)
    : scene(width, height), window(width, height), bitmap(width, height)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//performs a dracall, drawing a frame into the bitmap
void Engine::drawCall() {
    bitmap.clear();

    scene.toCameraSpace();
    Renderer::rayTrace(bitmap, scene);

    scene.toViewportSpace();
    // Renderer::rasterize(bitmap, scene);

    scene.cleanup();

    window.update(bitmap.getFrameBuffer());
}
