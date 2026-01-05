#include "scene/Scene.hpp"
#include "scene/bvhNode.hpp"
#include <iostream>

Scene::~Scene() {
    for (Mesh* mesh : objects) {
        delete mesh;
    }
}

std::vector<Mesh*>& Scene::getObjects() {
    return objects;
}

Camera& Scene::getCam() {
    return camera;
}

Mesh* Scene::addObject(Mesh* mesh) {
    return objects.emplace_back(mesh);
}

void Scene::setUpBvh() {
    tree = bvhNode{objects};
}