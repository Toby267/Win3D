#pragma once

#include "util/Vector.hpp"
#include "renderer/Ray.hpp"

class aabb {
private:
    Vector a;
    Vector b;

public:
    aabb(Vector min, Vector max);
    bool hit(const Ray& ray);
};

class bvhNode {

};
