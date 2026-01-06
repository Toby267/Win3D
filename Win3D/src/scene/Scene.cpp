#include "scene/Scene.hpp"
#include "scene/bvhNode.hpp"

Scene::~Scene() {
    for (Mesh* mesh : objects) {
        delete mesh;
    }

    if (tree) delete tree;
}

std::vector<Mesh*>& Scene::getObjects() {
    return objects;
}

void Scene::prepare() {
    for (Mesh* mesh : objects) {
        mesh->toWorldSpace();
        mesh->applyAffineTransform(camera.tranformationMatrix());
    }

    tree = new bvhNode{objects};
}

bool Scene::intersect(Ray& ray) {
    return tree->hit(ray);
}

void Scene::cleanup() {
    for (Mesh* mesh : objects) {
        mesh->reset();
    }

    delete tree;
}

Mesh* Scene::addObject(Mesh* mesh) {
    return objects.emplace_back(mesh);
}

Camera& Scene::getCam() {
    return camera;
}
