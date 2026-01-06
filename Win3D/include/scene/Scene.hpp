#pragma once

#include "renderer/Camera.hpp"
#include "scene/meshes/Mesh.hpp"
#include "scene/bvhNode.hpp"
#include <vector>

class Scene {
private:
    std::vector<Mesh*> objects{};
    Camera camera{};

    bvhNode tree;

public:
    ~Scene();

    std::vector<Mesh*>& getObjects();
    Camera& getCam();

    Mesh* addObject(Mesh* mesh);
    void setUpBvh();
};