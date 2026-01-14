#pragma once

#include "util/Colour.hpp"
#include "util/Vector.hpp"

struct HitRecord {
    float u;
    float v;
    float t;

    Colour c0;
    Colour c1;
    Colour c2;

    HitRecord() = default;
    HitRecord(Colour c0, Colour c1, Colour c2) : c0(c0), c1(c1), c2(c2) {};
} typedef HitRecord;

struct Ray {
    Vector origin;
    Vector direction;

    Colour col;
} typedef Ray;