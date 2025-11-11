#include "graphicsPipeline/GraphicsPipeline.hpp"
#include "graphicsPipeline/GraphicsPipelineInternals.hpp"

void GraphicsPipeline::DrawCall(const Scene& scene, Bitmap3D& bitmap, const Viewport& viewport) {
    processGeometry(scene, bitmap, viewport);
}