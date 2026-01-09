#pragma once

#include "util/Vector.hpp"
#include "renderer/Ray.hpp"

struct Aabb {
public:
    Vector a = Vector(0, 0, 0);
    Vector b = Vector(0, 0, 0);

    Aabb() = default;
    Aabb(Vector min, Vector max);
    Aabb(Aabb box1, Aabb box2);

    bool intersect(Ray& ray) const;

    float surfaceArea() const;
    Vector centroid() const;
};
