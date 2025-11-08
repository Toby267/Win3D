#include "scene/Scene.hpp"

void Scene::addObject(std::shared_ptr<Object3D> obj) {
    objects.push_back(obj);
}

std::vector<std::shared_ptr<Object3D>> Scene::getObjects() const {
    return objects;
}