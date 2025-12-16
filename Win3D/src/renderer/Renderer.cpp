#include "renderer/Renderer.hpp"
#include <iostream>

static float mollerTrumbore(Vector orig, Vector dir, Vector vert0, Vector vert1, Vector vert2);

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
    : window(width, height), bitmap(width, height), geometryProcessor(), rasterizer(bitmap),
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

    geometryProcessor.processGeometry(objects);

    /*fragments = */ rasterizer.rasterize(objects);

    /*fragmentShader.shade(fragments)*/

    /*bitmap.merge(fragments)*/

    window.update(bitmap.getFrameBuffer());
}


struct Ray {
    Vector origin;
    Vector direction;
    Colour col;
} typedef ray;

void Renderer::drawCallRayTraced(std::vector<Object3D> objects) {
    bitmap.clear();

    geometryProcessor.processGeometryRayTracing(objects);

    //these are defined in the camera
    int cameraWidth = 1280;
    int cameraHeight = 720;
    int focalDistance = 1000;

    int x = cameraWidth/2, y = cameraHeight/2;

    //loop through each pixel of the window
    for (int i = -cameraWidth/2; i < cameraWidth/2; i++) {
        for (int j = -cameraHeight/2; j < cameraHeight/2; j++) {
            Vector origin = Vector(0, 0, 0);
            Vector direction = Vector(i, j, focalDistance).normalise();
            Colour col = Colour::blue();

            Ray ray = Ray(origin, direction, col);

            //moller trumbore intersection test...
            float t = mollerTrumbore(origin, direction, Vector(-100, -100, 1500), Vector(0, 100, 1500), Vector(100, -100, 1500));
            if (t != -1) bitmap.drawPixel(x+i, y+j, 1000, ray.col);
        }
    }

    window.update(bitmap.getFrameBuffer());

    std::cin.get();
}

//returns t - the distance
float mollerTrumbore(Vector orig, Vector dir, Vector vert0, Vector vert1, Vector vert2) {
    Vector edge1, edge2, tvec, pvec, qvec;
    double det, inv_det;

    //find vectors for the two edges sharing vert0
    edge1 = vert1 - vert0;
    edge2 = vert2 - vert0;

    //begin calculating determinant - also used to calculate U parameter
    pvec = Vector::crossProduct(dir, edge2);

    //if determinant is near zero, ray lies in plane of triangle
    det = Vector::dotProduct(edge1, pvec);

    //for now, only implement the culling branch, if I need two faced triangles, implement the other branch later
    if (det < std::numeric_limits<float>::epsilon())
        return -1;

    //calculate distance from vert0 to ray origin
    tvec = orig - vert0;

    //calculate u parameter and test bounds
    double u = Vector::dotProduct(tvec, pvec);
    if (u < 0 || u > det)
        return -1;

    //prepare to test v parameter
    qvec = Vector::crossProduct(tvec, edge1);

    //calculate v parameter and test bounds
    double v = Vector::dotProduct(dir, qvec);
    if (v < 0 || u + v > det)
        return -1;

    //calculate t, scale parameters, ray intersects triangle
    double t = Vector::dotProduct(edge2, qvec);
    inv_det = 1.0 / det;
    t *= inv_det;

    return t;
}