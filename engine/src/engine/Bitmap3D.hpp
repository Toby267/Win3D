#pragma once

#include "util/Util.hpp"

#include <vector>

/**
 * Class representing a bitmap
 *
 * includes a frame buffer and z buffer, and is used for visibility determination in the raster pipeline
 */
class Bitmap3D {
private:
    int width, height;

    std::vector<unsigned char> frameBuffer;
    std::vector<double> zBuffer;

public:
    // constructors/destructor
    Bitmap3D(int width, int height);

    // getters/setters
    const std::vector<unsigned char>& getFrameBuffer() const { return frameBuffer; };

    // public methods
    void clear();
    void drawPixel(int x, int y, int z, Colour colour);
    void setPixel(int x, int y, Colour colour);
    void saveAsPPM(std::string path);
};
