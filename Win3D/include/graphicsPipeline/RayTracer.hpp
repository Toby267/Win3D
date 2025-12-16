#pragma once

#include "renderer/Bitmap3D.hpp"
#include "scene/Object3D.hpp"
#include "util/Vector.hpp"
#include "util/Colour.hpp"

struct Ray {
    Vector origin;
    Vector direction;
    Vector screenCoord;
    Colour col;
} typedef ray;

class RayTracer {
private:
    Bitmap3D& bitmap;

public:
    RayTracer(Bitmap3D& bmap);

    void trace(std::vector<Object3D>& objects);

private:
    float mollerTrumboreIntersection(Vector orig, Vector dir, Vector vert0, Vector vert1, Vector vert2);
    float barycentricIntersection();
    float waldMethodIntersection();
};