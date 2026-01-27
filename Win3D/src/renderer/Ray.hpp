#pragma once

#include "scene/core/SceneUtil.hpp"
#include "scene/objects//Materials.hpp"
#include "util/Util.hpp"

struct Ray {
    Vector origin;
    Vector direction;
} typedef Ray;

struct HitRecord {
    float u, v, t;
    Mat::Material mat = Mat::DisneyDiffuse{0.0, 0.0};
    Vertex v1, v2, v3;

} typedef HitRecord;

struct TrianglePoint {
    float u;
    float v;

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

    TrianglePoint() = default;
    TrianglePoint(Mat::Material mat, float u, float v, Colour c0, Colour c1, Colour c2, Vector n0, Vector n1, Vector n2)
        : mat(mat), u(u), v(v), c0(c0), c1(c1), c2(c2), n0(n0), n1(n1), n2(n2) {}
} typedef TrianglePoint;
