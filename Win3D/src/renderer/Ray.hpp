#pragma once

#include "scene/core/SceneUtil.hpp"
#include "scene/objects//Materials.hpp"
#include "util/Util.hpp"

struct Ray {
    Vector origin;
    Vector direction;
} typedef Ray;

struct HitRecord {
    Vertex v1, v2, v3;
    Mat::Material mat = Mat::DisneyDiffuse{0.0, 0.0};
    float u, v, t;
} typedef HitRecord;
