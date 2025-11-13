#include "graphicsPipeline/GraphicsPipeline.hpp"

#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

GraphicsPipeline::GraphicsPipeline(Bitmap3D& bmap)
    : rasterizer(bmap)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Passes a vector of objects through the graphics rendering pipeline, and renders them onto a bitmap/framebuffer
 * 
 * @param objects   the objects to pass throught the rendering pipeline
 * @param bmap      the bitmap to render to
 */
void GraphicsPipeline::drawCall(std::vector<Object3D>& objects) {    
    geometryProcessor.processGeometry(objects);

    /*fragments = */ rasterizer.rasterize(objects);

    /*fragmentShader.shade(fragments)*/

    /*bitmap.merge(fragments)*/
}