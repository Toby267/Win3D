#pragma once

#include <vector>

#include "util/Colour.hpp"

class Bitmap3D {
private:
    int width, height;

    std::vector<unsigned char> frameBuffer;
    std::vector<double> zBuffer;

public:
    //constructors/destructor
    Bitmap3D(int width, int height);

    //getters/setters
    std::vector<unsigned char>& getFrameBuffer();
    int getWidth();
    int getHeight();

    //public methods
    void clear();
    void drawPixel(int x, int y, int z, Colour c);
};
