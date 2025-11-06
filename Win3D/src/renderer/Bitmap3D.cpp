#include "renderer/Bitmap3D.hpp"
#include "util/Colour.hpp"

#include <cfloat>

Bitmap3D::Bitmap3D(int width, int height)
    : width(width), height(height)
{
    frameBuffer = new unsigned char[width*height*4];
    zBuffer = new double[width*height];

    for (int i = 0; i < width*height; i++)
        zBuffer[i] = -DBL_MAX;
}

Bitmap3D::~Bitmap3D() {
    delete[] frameBuffer;
    delete[] zBuffer;
}

void Bitmap3D::setPixel(int x, int y, int z, Colour c) {
    if (zBuffer[y*width + x] > z) return;

    int i = 4 * (y * width + x);
    frameBuffer[i + 0] = c.r;
    frameBuffer[i + 1] = c.g;
    frameBuffer[i + 2] = c.b;
    frameBuffer[i + 3] = c.a;
}

unsigned char* Bitmap3D::getFrameBuffer() {
    return frameBuffer;
}