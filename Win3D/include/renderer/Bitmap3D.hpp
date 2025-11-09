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

    Colour getCol(int x, int y);
    void drawPixel(int x, int y, int z, Colour c);
    void drawLine(Vector start, Vector end, Colour c1, Colour c2);
    void drawTriangle(Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3, Vector n1, Vector n2, Vector n3);
    void drawTriangle(Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3); //only use while developing the 3D one
};
