#include "scene/core/Scene.hpp"
#include "renderer/Camera.hpp"
#include "renderer/Ray.hpp"
#include "scene/objects/Mesh.hpp"
#include "scene/objects/PointLight.hpp"
#include "util/Util.hpp"

#include <cmath>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// default constructor taking in the screen width and height
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

// destructor
Scene::~Scene() {
    for (Mesh* mesh : objects) {
        delete mesh;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// methods for registering objects and lights
Mesh* Scene::addObject(Mesh* mesh) {
    return objects.emplace_back(mesh);
}
void Scene::addLight(PointLight light) {
    lights.emplace_back(light);
}

// transforms all meshes to camera space
void Scene::toCameraSpace() {
    for (Mesh* mesh : objects) {
        mesh->toWorldSpace();
        mesh->applyAffineTransform(camera.tranformationMatrix());
        mesh->transformNormals(camera.rotationMatrix());
        mesh->createAccelDataStrucutre();
    }
    for (PointLight light : lights) {
        light.applyAffineTransform(camera.tranformationMatrix());
    }
}

// transforms all meshes to viewport space
void Scene::toViewportSpace() {
    for (Mesh* mesh : objects) {
        mesh->applyTransform(camera.projectionMatrix());
        mesh->clip();
        mesh->applyAffineTransform(camera.viewportMatrix());
    }
}

// ray scene intersection
void Scene::intersect(const Ray& ray, HitRecord& record) const {
    for (const Mesh* mesh : objects) {
        HitRecord rec = mesh->intersect(ray);

        if (rec.t < record.t) {
            record = rec;
        }
    }
}

// resets all meshes and lights
void Scene::cleanup() {
    for (Mesh* mesh : objects) {
        mesh->reset();
    }
    for (PointLight light : lights) {
        light.reset();
    }
}
