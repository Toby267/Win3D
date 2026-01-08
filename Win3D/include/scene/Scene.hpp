#pragma once

#include "renderer/Camera.hpp"
#include "scene/meshes/Mesh.hpp"
#include "scene/bvhNode.hpp"
#include <vector>

class Scene {
private:
    std::vector<Mesh*> objects{};
    Camera camera{};

    bvhNode* tree = nullptr;

public:
    Scene(int screenWidth, int screenHeight);
    Scene() = default;
    ~Scene();

    void prepare();
    bool intersect(Ray& ray) const;
    void cleanup();

    Mesh* addObject(Mesh* mesh);

    //dont need the rest i think
    std::vector<Mesh> getObjects() const;
    const Camera& getCam() const;
};