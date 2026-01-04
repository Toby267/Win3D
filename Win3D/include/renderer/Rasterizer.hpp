#pragma once

#include "engine/Bitmap3D.hpp"
#include "scene/Mesh.hpp"
#include "scene/Scene.hpp"

class Rasterizer {
private:
    Scene& scene;

public:
    Rasterizer(Scene& sceneRef);

    void rasterize(Bitmap3D& bmap);

private:
    //private methods
    void drawTriangle(Bitmap3D& bmap, Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3);
    void drawLine(Bitmap3D& bmap, Vector start, Vector end, Colour c1, Colour c2);
};
