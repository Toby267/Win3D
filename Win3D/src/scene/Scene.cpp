#include "scene/Scene.hpp"

Scene::Scene() {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::vector<std::shared_ptr<Object3D>>& Scene::getObjects() const {
    return objects;
}

const Camera& Scene::getCamera() const {
    return *camera;
}

void Scene::setDepthOfField(int depth) {
    camera->setDepthOfField(depth);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//needs to be passed by non-ref in order to be shared
void Scene::addObject(std::shared_ptr<Object3D> obj) {
    objects.push_back(obj);
}

void Scene::setCamera(std::shared_ptr<Camera> cam) {
    camera = cam;
}