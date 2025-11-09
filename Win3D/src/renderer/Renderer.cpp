#include "renderer/Renderer.hpp"

#include "renderer/VertexShader.hpp"
#include "util/Matrix.hpp"

#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer::Renderer(int width, int height) :
    width(width), height(height)
{
    std::shared_ptr<Object3D> cube = std::make_shared<Object3D>(Object3D::cube());
    cube->setScale(Matrix::scale(100, 100, 100));
    cube->setTranslation(Matrix::translate(300, 300, 500));
    scene.addObject(cube);

    double alpha = 0.0;
    while (window.isAlive()) {
        alpha += std::numbers::pi/256;
        cube->setRotation(Matrix::rotation(0, -std::numbers::pi/16, -std::numbers::pi/16));

        drawCall();
        // std::this_thread::sleep_for(std::chrono::seconds(1));
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
