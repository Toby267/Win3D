#include "renderer/Renderer.hpp"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer::Renderer(int width, int height)
    : window(width, height), bitmap(width, height)
{

}

void Renderer::drawCall(std::vector<Object3D> objects) {
    bitmap.clear();

    pipeline.drawCall(objects, bitmap);

    window.update(bitmap.getFrameBuffer());
}
