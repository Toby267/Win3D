#pragma once

#include "scene/Object3D.hpp"
#include <memory>
#include <vector>

class Scene {
private:
    std::vector<std::shared_ptr<Object3D>> objects;

public:
    void addObject(std::shared_ptr<Object3D> obj);
    std::vector<std::shared_ptr<Object3D>> getObjects() const;
};