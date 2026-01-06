#pragma once

#include "scene/meshes/Mesh.hpp"
#include "scene/aabb.hpp"
#include <vector>

//has instance(s) of either left, right, left & right, or just data
//always has an aabb
class bvhNode {
private:
    aabb boundingBox;

    bvhNode* left = nullptr;
    bvhNode* right = nullptr;

    Mesh* data = nullptr;

public:
    bvhNode() = default;
    bvhNode(std::vector<Mesh*> objects);

    ~bvhNode();

    bool hit(Ray& ray);

private:
    float sweepSurfaceAreaHeuristic(std::vector<Mesh*>& axisOrderedObjects, int i);
};
