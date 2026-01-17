#include "scene/Scene.hpp"
#include "renderer/Camera.hpp"
#include "renderer/Ray.hpp"
#include "scene/BvhNode.hpp"
#include "util/Colour.hpp"
#include "util/Vector.hpp"

#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Scene::Scene(int screenWidth, int screenHeight) {
    //set up camera
    camera.position = Vector(0, 0, 0, 1);
    camera.direction = Vector(0, 0, 1, 0);
    camera.up = Vector(0, 1, 0, 0);

    //really only used to make scene management easier, but for now can be the same as the screen dimensions
    camera.apperatureHeight = screenHeight;
    camera.apperatureWidth = screenWidth;

    camera.fieldOfView = 60.0/360.0 * 2.0*std::numbers::pi;

    camera.nearFocalDistance = 1000;
    camera.farFocalDistance = 3000;

    camera.screenHeight = screenHeight;
    camera.screenWidth = screenWidth;

    
    //add a single light. TODO: move this to a addLight() method for use in Application.cpp
    lights.emplace_back(Vector(0, 0, 0), Colour::red(), 100);
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
const std::vector<PointLight>& Scene::getLights() const {
    return lights;
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

bool Scene::intersect(const Ray& ray, TrianglePoint& triangle, float& t) const {
    return tree->hit(ray, triangle, t);
}

void Scene::cleanup() {
    for (Mesh* mesh : objects) {
        mesh->reset();
    }

    delete tree;
}
