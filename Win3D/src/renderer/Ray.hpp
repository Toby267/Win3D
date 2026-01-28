#pragma once

#include "scene/objects//Materials.hpp"
#include "util/Util.hpp"

struct Ray {
    Vector origin;
    Vector direction;
} typedef Ray;

struct HitRecord {
    // Vertex v1, v2, v3;

    Colour c0;
    Colour c1;
    Colour c2;

    Vector n0;
    Vector n1;
    Vector n2;

    Vector v0;
    Vector v1;
    Vector v2;

    Mat::Material mat = Mat::DisneyDiffuse{0.0, 0.0};
    float u, v, t;
} typedef HitRecord;
