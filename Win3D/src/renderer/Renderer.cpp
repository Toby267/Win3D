#include "renderer/Renderer.hpp"

#include "graphicsPipeline/GraphicsPipeline.hpp"

#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer::Renderer(int width, int height, std::shared_ptr<Scene> s) :
    width(width), height(height), scene(s)
{

}

void Renderer::drawCall() {
    bitmap.clear();

    GraphicsPipeline::DrawCall(*scene, bitmap);

    window.update(bitmap.getFrameBuffer());
}
