#pragma once

#include "renderer/Camera.hpp"
#include "renderer/Ray.hpp"
#include "scene/objects//Mesh.hpp"
#include "scene/dataStructures/BvhNode.hpp"
#include "scene/objects/PointLight.hpp"
#include <vector>

class Scene {
private:
    std::vector<Mesh*> objects{};
    std::vector<PointLight> lights{};
    Camera camera{};

    // BvhNode* tree = nullptr;

public:
    //constructors/destructor
    Scene(int screenWidth, int screenHeight);
    Scene() = default;
    ~Scene();

    //getters/setters
    const Camera& getCam() const { return camera; }
    const std::vector<PointLight>& getLights() const { return lights; }
    const std::vector<Mesh*>& getObjects() const { return objects; }
    
    //public methods
    Mesh* addObject(Mesh* mesh);

    void toCameraSpace();
    void toViewportSpace();
    
    void intersect(const Ray& ray, HitRecord& record) const;
    void cleanup();    
};