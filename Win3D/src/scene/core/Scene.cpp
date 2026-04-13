#include "scene/core/Scene.hpp"
#include "renderer/Camera.hpp"
#include "renderer/Ray.hpp"
#include "scene/objects/Mesh.hpp"
#include "util/Util.hpp"

#include <cmath>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Scene::Scene(int screenWidth, int screenHeight) {
    //set up camera
    camera.position = Vector(0, 0, 0, 1);
    camera.direction = Vector(0, 0, 1, 0);
    camera.up = Vector(0, 1, 0, 0);

    camera.apperatureHeight = screenHeight;
    camera.apperatureWidth = screenWidth;

    camera.nearFocalDistance = 1000;
    camera.farFocalDistance = 3000;

    camera.screenHeight = screenHeight;
    camera.screenWidth = screenWidth;

    camera.fieldOfView = std::atan(camera.apperatureHeight / camera.nearFocalDistance);
}

Scene::~Scene() {
    for (Mesh* mesh : objects) {
        delete mesh;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mesh* Scene::addObject(Mesh* mesh) {
    return objects.emplace_back(mesh);
}

void Scene::addLight(PointLight light) {
    lights.emplace_back(light);
}

void Scene::toCameraSpace() {
    for (Mesh* mesh : objects) {
        mesh->toWorldSpace();
        mesh->applyAffineTransform(camera.tranformationMatrix());
        mesh->transformNormals(camera.rotationMatrix());
        mesh->createAccelDataStrucutre();
    }
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
}
