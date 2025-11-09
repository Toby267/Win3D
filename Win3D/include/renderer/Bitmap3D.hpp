#pragma once

#include "util/Colour.hpp"
#include "util/Vector.hpp"
#include <vector>

class Bitmap3D {
private:
    int width, height;

    std::vector<unsigned char> frameBuffer;
    std::vector<double> zBuffer;

public:
    //constructors/destructor
    Bitmap3D(int width, int height);

    //getters/setters
    const std::vector<unsigned char>& getFrameBuffer();

    //public methods
    void clear();

    void drawPixel(int x, int y, int z, Colour c);
};
