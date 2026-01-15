#pragma once

#include "util/Colour.hpp"
#include "util/Vector.hpp"

struct Ray {
    Vector origin;
    Vector direction;

    Colour col;
} typedef Ray;

struct HitRecord {
    float u;
    float v;
    float t;

    Colour c0;
    Colour c1;
    Colour c2;

    HitRecord() = default;
    HitRecord(float t) : t(t) {};
    HitRecord(Colour c0, Colour c1, Colour c2) : c0(c0), c1(c1), c2(c2) {};
} typedef HitRecord;


// after interpolating the base colour, you multiply this by the light colour and light intensity before plugging into the brdf

// step 1 - move eval to rayTracer.cpp instead of mesh.hit();
// step 2 - add a light in scene.hpp and use that as the out
// step 3 - add a list of normals in mesh.hpp and use that in eval