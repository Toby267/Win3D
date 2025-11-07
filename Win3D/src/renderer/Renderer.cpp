#include "renderer/Renderer.hpp"
#include "util/Vector.hpp"
#include "util/Matrix.hpp"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer::Renderer(int width, int height) :
    width(width), height(height),
    window(std::make_unique<Window>(width, height)),
    bitmap(std::make_unique<Bitmap3D>(width, height))
{
    while (window->isAlive()) {
        drawCall();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::drawCall() {
    bitmap->drawTriangle(Vector(0, height-1, 0), Vector(width/2.0, 0, 0), Vector(width-1, height-1, 0), Colour(255, 0, 0), Colour(0, 255, 0), Colour(0, 0, 255));
    window->update(bitmap->getFrameBuffer());
}

void Renderer::test() {

}
