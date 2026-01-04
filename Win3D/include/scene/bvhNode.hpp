#pragma once

#include "Mesh.hpp"
#include "scene/Object.hpp"
#include "scene/aabb.hpp"
#include <memory>
#include <vector>


//would be easier to just use c style memory management
class bvhNode : public Object {
private:
    std::unique_ptr<Object> left = nullptr;
    std::unique_ptr<Object> right = nullptr;

    aabb boundingBox;

public:
    bvhNode() = default;
    bvhNode(std::shared_ptr<Object> obj); //for creating a leaf node - typically pass in a mesh
    bvhNode(std::vector<std::shared_ptr<Object>>& objects); //for creating a bvhNode
    bvhNode(std::vector<std::shared_ptr<Object>>& objects, int start, int end);

    bool hit(Ray& ray) const override;
    aabb getBBox() const override;

private:
    float sweepSurfaceAreaHeuristic(std::vector<std::shared_ptr<Object>>& axisOrderedObjects, int i);
};
