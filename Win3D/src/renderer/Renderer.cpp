#include "renderer/Renderer.hpp"

#include "renderer/VertexShader.hpp"
#include "util/Vector.hpp"
#include "util/Matrix.hpp"

#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer::Renderer(int width, int height) :
    width(width), height(height),
    window(std::make_unique<Window>(width, height)),
    bitmap(std::make_unique<Bitmap3D>(width, height)),
    scene(std::make_unique<Scene>())
{
    while (window->isAlive()) {
        drawCall();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::drawCall() {
    scene->addObject(Object3D::cube(Matrix::scale(100, 100, 100), Matrix::translate(width/2.0, height/2.0, 0)));

    VertexShader::draw(*scene, *bitmap);

    window->update(bitmap->getFrameBuffer());
}

void Renderer::test() {

}
