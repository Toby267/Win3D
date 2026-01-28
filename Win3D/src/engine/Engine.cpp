#include "engine/Engine.hpp"

#include "engine/Bitmap3D.hpp"
#include "engine/Window.hpp"
#include "renderer/Renderer.hpp"
#include "scene/core/Scene.hpp"
#include <iostream>

Engine::Engine(int w, int h)
    : scene(w, h), window(w, h), bitmap(w, h)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//performs a dracall, drawing a frame into the bitmap
void Engine::drawCall() {
    bitmap.clear();

    scene.toCameraSpaceOld();
    Renderer::rayTrace(bitmap, scene);

    scene.toViewportSpace();
    // Renderer::rasterize(bitmap, scene);

    scene.cleanupOld();

    window.update(bitmap.getFrameBuffer());

    std::cin.get();
}
