#include "scene/Scene.hpp"
#include "scene/bvhNode.hpp"
#include <vector>

Scene::~Scene() {
    for (Mesh* mesh : objects) {
        delete mesh;
    }

    if (tree) delete tree;
}

std::vector<Mesh> Scene::getObjects() const {
    std::vector<Mesh> obs{};
    
    for (Mesh* m : objects)
        obs.emplace_back(*m);

    return obs;
}

void Scene::prepare() {
    for (Mesh* mesh : objects) {
        mesh->toWorldSpace();
        mesh->applyAffineTransform(camera.tranformationMatrix());
    }

    tree = new bvhNode{objects};
}

bool Scene::intersect(Ray& ray) const {
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

const Camera& Scene::getCam() const {
    return camera;
}
