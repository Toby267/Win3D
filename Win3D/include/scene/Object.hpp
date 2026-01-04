#pragma once

#include "renderer/Ray.hpp"
#include "scene/aabb.hpp"

class Object {
public:
    virtual bool hit(Ray& ray) const = 0;
    virtual aabb getBBox() const = 0;
};