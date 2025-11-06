#pragma once

#include "util/Colour.hpp"

class Bitmap3D {
private:
    int width, height;

    unsigned char* frameBuffer;
    double* zBuffer;

public:
    Bitmap3D(int width, int height);
    ~Bitmap3D();

    void setPixel(int x, int y, int z, Colour c);
    unsigned char* getFrameBuffer();
};