#pragma once

#include "renderer/Bitmap3D.hpp"
#include "scene/Object3D.hpp"

class Rasterizer {
private:


public:

    void rasterize(std::vector<Object3D>& objects, Bitmap3D& bmap);
    
    void drawTriangle(Bitmap3D& bmap, Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3);
    void drawLine(Bitmap3D& bmap, Vector start, Vector end, Colour c1, Colour c2);
};