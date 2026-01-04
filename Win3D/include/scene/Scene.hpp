#pragma once

#include "scene/Mesh.hpp"
#include "scene/bvhNode.hpp"
#include <vector>

class Scene {
private:
    std::vector<Mesh> objects{};
    bvhNode tree{};

public:
    Scene();

    std::vector<Mesh> getObjects();
};