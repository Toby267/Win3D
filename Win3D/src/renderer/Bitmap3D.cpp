#include "renderer/Bitmap3D.hpp"
#include "util/Colour.hpp"

#include <cfloat>
#include <cstdlib>
#include <iostream>

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
    if (x >= width || x < 0 || y >= height || y < 0) return;
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

void Bitmap3D::DrawLine(Vector start, Vector end, Colour c1, Colour c2) {
    int x1 = start.x(), y1 = start.y(), z1 = start.z();
    int x2 = end.x(),   y2 = end.y(),   z2 = end.z();

    double dx = x2-x1, dy = y2-y1, dz = z2-z1;
    double dr = c2.r-c1.r, dg = c2.g-c1.g, db = c2.b-c1.b, da = c2.a - c1.a;

    setPixel(x1, y1, z1, c1);
    if (std::abs(dx) > std::abs(dy)) {
        if (dx == 0) return;

        double ySlope = dy / dx;
        double zSlope = dz / dx;
        double rSlope = dr / dx;
        double gSlope = dg / dx;
        double bSlope = db / dx;
        double aSlope = da / dx;

        int yError    = (y1   - ySlope * x1);
        int zError    = (z1   - zSlope * x1);
        int rError    = (c1.r - rSlope * x1);
        int gError    = (c1.g - gSlope * x1);
        int bError    = (c1.b - bSlope * x1);
        int aError    = (c1.a - aSlope * x1);

        int xStep = dx < 0 ? -1 : 1;

        while (x1 != x2) {
            x1 += xStep;
            y1   = (ySlope * x1) + yError;
            z1   = (zSlope * x1) + zError;
            c1.r = (rSlope * x1) + rError;
            c1.g = (gSlope * x1) + gError;
            c1.b = (bSlope * x1) + bError;
            c1.a = (aSlope * x1) + aError;
            setPixel(x1, y1, z1, c1);
        }
    }
    else {
        if (dy == 0) return;

        double xSlope = dx / dy;
        double zSlope = dz / dy;
        double rSlope = dr / dy;
        double gSlope = dg / dy;
        double bSlope = db / dy;
        double aSlope = da / dy;

        int xError    = (x1   - xSlope * y1);
        int zError    = (z1   - zSlope * y1);
        int rError    = (c1.r - rSlope * y1);
        int gError    = (c1.g - gSlope * y1);
        int bError    = (c1.b - bSlope * y1);
        int aError    = (c1.a - aSlope * y1);

        int yStep = dy < 0 ? -1 : 1;

        while (y1 != y2) {
            y1 += yStep;
            x1   = (xSlope * y1) + xError;
            z1   = (zSlope * y1) + zError;
            c1.r = (rSlope * y1) + rError;
            c1.g = (gSlope * y1) + gError;
            c1.b = (bSlope * y1) + bError;
            c1.a = (aSlope * y1) + aError;
            setPixel(x1, y1, z1, c1);
        }
    }
}