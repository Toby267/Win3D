#include "renderer/Renderer.hpp"
#include <iostream>

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
    : window(width, height), bitmap(width, height),
    rasterizer(bitmap), tracer(bitmap),
    width(width), height(height)
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
    // drawCallRaster(objects);
    drawCallRayTraced(objects);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ PRIVATE METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::drawCallRaster(std::vector<Object3D> objects) {
    bitmap.clear();

    processGeometry(objects);

    /*fragments = */ rasterizer.rasterize(objects);

    /*fragmentShader.shade(fragments)*/

    /*bitmap.merge(fragments)*/

    window.update(bitmap.getFrameBuffer());
}

void Renderer::drawCallRayTraced(std::vector<Object3D> objects) {
    bitmap.clear();

    processGeometryRayTracing(objects);

    /*fragments =*/ tracer.trace(objects);

    window.update(bitmap.getFrameBuffer());

    // std::cin.get();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
object space axis:              x = right,  y = up, z = forward
world space axis:               x = right,  y = up, z = forward
camera space axis:              x = right,  y = up, z = forward
canonical view cube axis:       x = right,  y = up, z = forward
screen space axis:              x = right, -y = up, z = forward

object space range:              infinite
world space range:               infinite
camera space range:              infinite
canonical view cube range:       (-1, -1, -1) to (1, 1, 1)
screen space range:              defined by the viewport struct

object space -> world space -> camera space -> canonical view cube -> screen space
*/


void Renderer::processGeometry(std::vector<Object3D>& objects) {
    for (Object3D& obj : objects) {
        //step 0 - tesselation

        //step 1 - transform the object into world space
        obj.transform();

        //step 2 - transform the objects to camera space
        obj.applyAffineTransformation(camera.tranformationMatrix());

        //step 3 - vertex shading

        //step 3 - transform the objects to clip space
        obj.applyTransformation(camera.projectionMatrix());

        //step 5 - clip the objects
        obj.clip();

        //step 6 - transform the objects to screen space
        obj.applyAffineTransformation(viewport.tranformationMatrix());
    }
}

void Renderer::processGeometryRayTracing(std::vector<Object3D>& objects) {
    for (Object3D& obj : objects) {
        //step 0 - tesselation

        //step 1 - transform the object into world space
        obj.transform();

        //step 2 - transform the objects to camera space
        obj.applyAffineTransformation(camera.tranformationMatrix());

        //step 3 - vertex shading
    }
}
