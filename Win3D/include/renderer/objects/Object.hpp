#pragma once

#include "renderer/Ray.hpp"

class Object {
public:
    virtual bool hit(Ray& ray) const = 0;
};