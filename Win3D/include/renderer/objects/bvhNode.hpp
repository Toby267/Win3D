#pragma once

#include "Mesh.hpp"
#include "renderer/objects/Object.hpp"
#include "renderer/objects/aabb.hpp"
#include <memory>

class bvhNode : public Object {
private:
    std::shared_ptr<Object> left = nullptr;
    std::shared_ptr<Object> right = nullptr;

    aabb boundingBox;

public:
    bvhNode(std::shared_ptr<Object> obj); //for creating a leaf node - typically pass in a mesh
    bvhNode(std::vector<std::shared_ptr<Object>>& objects); //for creating a bvhNode

    bool hit(Ray& ray) const override;

private:
    float sweepSurfaceAreaHeuristic(std::shared_ptr<Object> axisOrderedObjects, int i);
};
