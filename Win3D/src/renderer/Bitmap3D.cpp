#include "renderer/Bitmap3D.hpp"
#include "util/Colour.hpp"

#include <cfloat>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Bitmap3D::Bitmap3D(int width, int height)
    : width(width), height(height)
{
    frameBuffer = std::vector<unsigned char>(width*height*4, 0);
    zBuffer = std::vector<double>(width*height, DBL_MAX);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::vector<unsigned char>& Bitmap3D::getFrameBuffer() {
    return frameBuffer;
}

int Bitmap3D::getWidth() {
    return width;
}
int Bitmap3D::getHeight() {
    return height;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Bitmap3D::clear() {
    for (int i = 0; i < width*height; i++) {
        zBuffer[i] = DBL_MAX;

        frameBuffer[4*i + 0] = 0;
        frameBuffer[4*i + 1] = 0;
        frameBuffer[4*i + 2] = 0;
        frameBuffer[4*i + 3] = 255;
    }
}

void Bitmap3D::drawPixel(int x, int y, int z, Colour c) {
    //if z < 0 because the camera will be oriented at 0, 0, 0 facing +z, so it doesn't want to get anything that is behind it
    //wait, doesn't me having to put this here to avoid this bug implying that the cameras projection isn't working
    if (x >= width || x < 0 || y >= height || y < 0) return;
    z += 20000;
    if (zBuffer[y*width + x] < z) return;

    zBuffer[y*width + x] = z;
    
    int i = 4 * (y * width + x);
    frameBuffer[i + 0] = c.r;
    frameBuffer[i + 1] = c.g;
    frameBuffer[i + 2] = c.b;
    frameBuffer[i + 3] = c.a;
}
