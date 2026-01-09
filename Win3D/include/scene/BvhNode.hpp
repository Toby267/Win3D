#pragma once

#include "scene/Mesh.hpp"
#include "scene/Aabb.hpp"
#include <vector>

//has instance(s) of either left, right, left & right, or just data
//always has an aabb
class BvhNode {
private:
    Aabb boundingBox;

    BvhNode* left = nullptr;
    BvhNode* right = nullptr;

    Mesh* data = nullptr;

public:
    BvhNode(std::vector<Mesh*> objects);

    ~BvhNode();

    bool hit(Ray& ray) const;
    void print() const;

private:
    float sweepSurfaceAreaHeuristic(std::vector<Mesh*>& axisOrderedObjects, int i);
};
