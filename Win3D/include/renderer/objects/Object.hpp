#pragma once

#include "renderer/Ray.hpp"
#include "renderer/objects/aabb.hpp"

class Object {
public:
    virtual bool hit(Ray& ray) const = 0;
    aabb boundingBox{};
};