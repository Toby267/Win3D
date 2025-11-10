#include "graphicsPipeline/GraphicsPipeline.hpp"
#include "graphicsPipeline/GeometryProcessor.hpp"

void GraphicsPipeline::DrawCall(const Scene& scene, Bitmap3D& bitmap) {
    GeometryProcessor::draw(scene, bitmap);
}