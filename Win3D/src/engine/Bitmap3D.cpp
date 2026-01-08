#include "engine/Bitmap3D.hpp"

#include <cfloat>
#include <vector>

#include "util/Colour.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Default constructor
 *
 * @param width     the width of the bitmap
 * @param height    the height of the bitmap
 */
Bitmap3D::Bitmap3D(int width, int height)
    : width(width), height(height)
{
    frameBuffer = std::vector<unsigned char>(width*height*4, 0);
    zBuffer = std::vector<double>(width*height, DBL_MAX);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//clears the bitmap
void Bitmap3D::clear() {
    for (int i = 0; i < width*height; i++) {
        zBuffer[i] = DBL_MAX;

        frameBuffer[4*i + 0] = 0;
        frameBuffer[4*i + 1] = 0;
        frameBuffer[4*i + 2] = 0;
        frameBuffer[4*i + 3] = 255;
    }
}

//draws a pixel onto the frame buffer
void Bitmap3D::drawPixel(int x, int y, int z, Colour c) {
    if (x >= width || x < 0 || y >= height || y < 0) return;
    z += 20000;
    if (zBuffer[y*width + x] < z) return;

    zBuffer[y*width + x] = z;
    
    int i = 4 * (y * width + x);
    frameBuffer[i + 0] = c.r();
    frameBuffer[i + 1] = c.g();
    frameBuffer[i + 2] = c.b();
    frameBuffer[i + 3] = c.a();
}
