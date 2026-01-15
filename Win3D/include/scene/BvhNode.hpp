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
    //constructors/destructor
    BvhNode(std::vector<Mesh*> objects);
    ~BvhNode();

    //public methods
    bool hit(const Ray& ray, TrianglePoint& triangle, float& t) const;
    void print() const;

private:
    //private methods
    float sweepSurfaceAreaHeuristic(std::vector<Mesh*>& axisOrderedObjects, int i);
};
