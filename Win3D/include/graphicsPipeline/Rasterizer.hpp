#pragma once

#include "renderer/Bitmap3D.hpp"
#include "scene/Object3D.hpp"

class Rasterizer {
private:
    Bitmap3D& bitmap;

public:

    Rasterizer(Bitmap3D& bmap);

    void rasterize(std::vector<Object3D>& objects);
    
    void drawTriangle(Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3);
    void drawLine(Vector start, Vector end, Colour c1, Colour c2);
};