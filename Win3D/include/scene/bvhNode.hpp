#pragma once

#include "scene/Mesh.hpp"
#include "scene/aabb.hpp"
#include <memory>
#include <vector>


//would be easier to just use c style memory management
class bvhNode {
private:
    bvhNode* left = nullptr;
    bvhNode* right = nullptr;

    Mesh* data = nullptr;

    aabb boundingBox;

public:
    bvhNode() = default;
    bvhNode(std::shared_ptr<Mesh> obj); //for creating a leaf node - typically pass in a mesh
    bvhNode(std::vector<std::shared_ptr<Mesh>>& objects); //for creating a bvhNode
    bvhNode(std::vector<std::shared_ptr<Mesh>>& objects, int start, int end);

    bool hit(Ray& ray) const;
    aabb getBBox() const;

private:
    float sweepSurfaceAreaHeuristic(std::vector<std::shared_ptr<Mesh>>& axisOrderedObjects, int i);
};
