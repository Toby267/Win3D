#pragma once

#include "scene/objects//Materials.hpp"
#include "util/Util.hpp"

struct Ray {
    Vector origin;
    Vector direction;
} typedef Ray;

struct HitRecord {
    Colour c0, c1, c2;              // per vertex colours
    Vector n0, n1, n2;              // per vertex normals
    Vector v0, v1, v2;              // per vertex positions
    double uv0[2], uv1[2], uv2[2];  // per vertex UV cordinates

    Mat::Material mat = Mat::DisneyDiffuse{0.0, 0.0};
    double u, v, t;                 // barycentric uv coordinates and t value
} typedef HitRecord;
