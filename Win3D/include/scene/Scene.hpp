#pragma once

#include "renderer/Camera.hpp"
#include "scene/Mesh.hpp"
#include "scene/BvhNode.hpp"

#include <vector>

class Scene {
private:
    std::vector<Mesh*> objects{};
    Camera camera{};

    BvhNode* tree = nullptr;

public:
    //constructors/destructor
    Scene(int screenWidth, int screenHeight);
    Scene() = default;
    ~Scene();

    //getters/setters
    const Camera& getCam() const;
    std::vector<Mesh> getObjects() const;
    
    //public methods
    Mesh* addObject(Mesh* mesh);

    void prepare();
    bool intersect(Ray& ray) const;
    void cleanup();    
};