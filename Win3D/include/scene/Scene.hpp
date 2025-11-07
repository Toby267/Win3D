#pragma once

#include "scene/Object3D.hpp"
#include <vector>


class Scene {
private:
    std::vector<Object3D> objects;

public:
    void addObject(Object3D obj);
};