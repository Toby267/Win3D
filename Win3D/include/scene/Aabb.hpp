#pragma once

#include "util/Vector.hpp"
#include "renderer/Ray.hpp"

struct Aabb {
    Vector a = Vector(0, 0, 0);
    Vector b = Vector(0, 0, 0);

    //constructors/destructor
    Aabb() = default;
    Aabb(Vector min, Vector max);
    Aabb(Aabb box1, Aabb box2);

    //public methods
    bool intersect(Ray& ray) const;
    float surfaceArea() const;
    Vector centroid() const;
};
