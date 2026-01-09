#include "scene/Scene.hpp"
#include "scene/BvhNode.hpp"

#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Scene::Scene(int screenWidth, int screenHeight) {
    camera.screenHeight = screenHeight;
    camera.screenHeight = screenHeight;
}

Scene::~Scene() {
    for (Mesh* mesh : objects) {
        delete mesh;
    }

    if (tree) delete tree;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

const Camera& Scene::getCam() const {
    return camera;
}

std::vector<Mesh> Scene::getObjects() const {
    std::vector<Mesh> obs{};
    
    for (Mesh* m : objects)
        obs.emplace_back(*m);

    return obs;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mesh* Scene::addObject(Mesh* mesh) {
    return objects.emplace_back(mesh);
}

void Scene::prepare() {
    for (Mesh* mesh : objects) {
        mesh->toWorldSpace();
        mesh->applyAffineTransform(camera.tranformationMatrix());
    }

    tree = new BvhNode{objects};
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
