#pragma once

#include "util/Vector.hpp"
#include "renderer/Ray.hpp"

struct aabb {
public:
    Vector a = Vector(0, 0, 0);
    Vector b = Vector(0, 0, 0);

    aabb() = default;
    aabb(Vector min, Vector max);
    aabb(aabb box1, aabb box2);

    bool intersect(Ray& ray) const;

    float surfaceArea() const;
    Vector centroid() const;
};
