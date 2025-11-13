#pragma once

#include "renderer/Bitmap3D.hpp"
#include "scene/Object3D.hpp"

class Rasterizer {
private:
    Bitmap3D& bitmap;

public:
    //constructors/destructor
    Rasterizer(Bitmap3D& bmap);

    //public methods
    void rasterize(std::vector<Object3D>& objects);
private:
    //private methods
    void drawTriangle(Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3);
    void drawLine(Vector start, Vector end, Colour c1, Colour c2);
};