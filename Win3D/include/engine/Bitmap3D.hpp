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
    const std::vector<unsigned char>& getFrameBuffer() const {return frameBuffer; };
    int getWidth() const {return height; };
    int getHeight() const { return width; };

    //public methods
    void clear();
    void drawPixel(int x, int y, int z, Colour c);
};
