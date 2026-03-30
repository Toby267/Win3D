#pragma once

#include "scene/objects//Materials.hpp"
#include "util/Util.hpp"

struct Ray {
    Vector origin;
    Vector direction;
} typedef Ray;

struct HitRecord {
    Colour c0, c1, c2;
    Vector n0, n1, n2;
    Vector v0, v1, v2;

    Mat::Material mat = Mat::DisneyDiffuse{0.0, 0.0};
    double u, v, t;
} typedef HitRecord;
