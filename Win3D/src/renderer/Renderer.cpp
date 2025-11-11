#include "renderer/Renderer.hpp"

#include "graphicsPipeline/GraphicsPipeline.hpp"

#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer::Renderer(int width, int height, int depthOfField, int FieldOfView, std::shared_ptr<Scene> s) :
    width(width), height(height), depthOfField(depthOfField), FieldOfView(FieldOfView), scene(s)
{
    scene->setDepthOfField(depthOfField);
}

void Renderer::drawCall() {
    bitmap.clear();

    GraphicsPipeline::DrawCall(*scene, bitmap, viewport);

    window.update(bitmap.getFrameBuffer());
}
