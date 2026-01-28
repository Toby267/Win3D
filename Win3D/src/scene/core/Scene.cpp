#include "scene/core/Scene.hpp"
#include "renderer/Camera.hpp"
#include "renderer/Ray.hpp"
#include "scene/dataStructures/BvhNode.hpp"
#include "scene/objects/Mesh.hpp"
#include "util/Util.hpp"

#include <limits>
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

    // if (tree) delete tree;
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
        mesh->updateAccelDataStrucutre();
    }

    // tree = new BvhNode{objects};
}

void Scene::toViewportSpace() {
    for (Mesh* mesh : objects) {
        mesh->applyTransform(camera.projectionMatrix());
        mesh->clip();
        mesh->applyAffineTransform(camera.viewportMatrix());
    }
}

void Scene::intersect(const Ray& ray, HitRecord& record) const {
    for (const Mesh* mesh : objects) {
        HitRecord rec = mesh->intersect(ray);

        if (rec.t < record.t) {
            record = rec;
        }
    }
}

void Scene::cleanup() {
    for (Mesh* mesh : objects) {
        mesh->reset();
    }

    // delete tree;
}
