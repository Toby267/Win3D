#pragma once

#include "renderer/Camera.hpp"
#include "scene/Mesh.hpp"
#include "scene/bvhNode.hpp"
#include <vector>

class Scene {
private:
    std::vector<Mesh> objects{};
    Camera camera{};

    bvhNode tree{};

public:
    Scene();

    std::vector<Mesh> getObjects();
    const Camera& getCam();
};