#include "renderer/Renderer.hpp"

#include "renderer/VertexShader.hpp"
#include "util/Matrix.hpp"

#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer::Renderer(int width, int height) :
    width(width), height(height),
    window(width, height),
    bitmap(width, height),
    scene()
{
    std::shared_ptr<Object3D> cube = std::make_shared<Object3D>(Object3D::cube());
    cube->setScale(Matrix::scale(100, 100, 100));
    cube->setTranslation(Matrix::translate(width/2.0, height/2.0, 0));
    scene.addObject(cube);

    double alpha = 0.0;
    while (window.isAlive()) {
        alpha +=  std::numbers::pi/18;
        cube->setRotation(Matrix::rotation(alpha, alpha, std::numbers::pi/4));

        drawCall();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ PRIVATE METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::drawCall() {
    bitmap.clear();

    VertexShader::draw(scene, bitmap);

    window.update(bitmap.getFrameBuffer());
}
