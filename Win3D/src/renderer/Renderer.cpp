#include "renderer/Renderer.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Default constructor that sets up the renderer
 * 
 * @param width     the width of the screen
 * @param height    the height of the scrren
 */
Renderer::Renderer(int width, int height)
    : window(width, height), bitmap(width, height), geometryProcessor(), rasterizer(bitmap)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Passes a vector of objects through the graphics rendering pipeline, and renders them the bitmap, then updates the window
 * 
 * @param objects   the objects to pass throught the rendering pipeline
 */
void Renderer::drawCall(std::vector<Object3D> objects) {
    bitmap.clear();

    geometryProcessor.processGeometry(objects);

    /*fragments = */ rasterizer.rasterize(objects);

    /*fragmentShader.shade(fragments)*/

    /*bitmap.merge(fragments)*/

    window.update(bitmap.getFrameBuffer());
}
