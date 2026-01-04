#pragma once

#include "util/Vector.hpp"
#include "renderer/Ray.hpp"

class aabb {
private:
    Vector a = Vector(0, 0, 0);
    Vector b = Vector(0, 0, 0);

public:
    aabb() = default;
    aabb(Vector min, Vector max);
    bool intersect(const Ray& ray) const;

    float surfaceArea();
    Vector centroid();
};
