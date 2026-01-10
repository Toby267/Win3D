#include "scene/Scene.hpp"
#include "renderer/Camera.hpp"
#include "scene/BvhNode.hpp"

#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Scene::Scene(int screenWidth, int screenHeight) {
    camera.screenHeight = screenHeight;
    camera.screenWidth = screenWidth;
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

const std::vector<Mesh*>& Scene::getObjects() const {
    return objects;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mesh* Scene::addObject(Mesh* mesh) {
    return objects.emplace_back(mesh);
}

void Scene::toCameraSpace() {
    for (Mesh* mesh : objects) {
        mesh->toWorldSpace();
        mesh->applyAffineTransform(camera.tranformationMatrix());
    }

    tree = new BvhNode{objects};
}

void Scene::toViewportSpace() {
    for (Mesh* mesh : objects) {
        mesh->applyTransform(camera.projectionMatrix());
        mesh->clip();
        mesh->applyAffineTransform(camera.viewportMatrix());
    }
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
