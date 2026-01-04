#include "scene/Scene.hpp"

Scene::Scene() {
    
}

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
    objects.emplace_back(mesh);
    return mesh;
}