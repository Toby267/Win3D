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
    : window(width, height), bitmap(width, height), pipeline(bitmap)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Perfoms a draw call
 * 
 * @param objects the objects to be drawn onto the screen
 */
void Renderer::drawCall(std::vector<Object3D> objects) {
    bitmap.clear();

    pipeline.drawCall(objects);

    window.update(bitmap.getFrameBuffer());
}
