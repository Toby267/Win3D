#pragma once

#include "scene/Materials.hpp"
#include "util/Colour.hpp"
#include "util/Vector.hpp"

struct Ray {
    Vector origin;
    Vector direction;
} typedef Ray;

struct HitRecord {
    float u;
    float v;
    float t;

    Colour c0;
    Colour c1;
    Colour c2;

    Vector n0;
    Vector n1;
    Vector n2;

    Mat::Material m = Mat::DisneyDiffuse{0.0, 0.0};

    HitRecord() = default;
    HitRecord(float t) : t(t) {};
} typedef HitRecord;


// after interpolating the base colour, you multiply this by the light colour and light intensity before plugging into the brdf

// step 1 - move eval to rayTracer.cpp instead of mesh.hit();
// step 2 - add a light in scene.hpp and use that as the out
// step 3 - add a list of normals in mesh.hpp and use that in eval