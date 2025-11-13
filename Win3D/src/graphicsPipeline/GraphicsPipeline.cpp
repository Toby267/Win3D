#include "graphicsPipeline/GraphicsPipeline.hpp"

#include <vector>

/**
 * Passes a vector of objects through the graphics rendering pipeline, and renders them onto a bitmap/framebuffer
 * 
 * @param objects   the objects to pass throught the rendering pipeline
 * @param bmap      the bitmap to render to
 */
void GraphicsPipeline::drawCall(std::vector<Object3D>& objects, Bitmap3D& bmap) {    

    geometryProcessor.processGeometry(objects);

    rasterizer.rasterize(objects, bmap);
}