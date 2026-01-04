#pragma once

#include "renderer/Camera.hpp"
#include "util/Matrix.hpp"
#include "engine/Bitmap3D.hpp"
#include "scene/Mesh.hpp"

class CameraRasterizer {
private:
    Camera camera{};

public:
    void rasterize(std::vector<Mesh>& objects, Bitmap3D& bmap);

private:
    //private methods
    void drawTriangle(Bitmap3D& bmap, Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3);
    void drawLine(Bitmap3D& bmap, Vector start, Vector end, Colour c1, Colour c2);
};
