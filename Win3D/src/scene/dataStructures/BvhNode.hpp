#pragma once

#include "renderer/Ray.hpp"
#include "scene/objects/Mesh.hpp"
#include "scene/dataStructures/Aabb.hpp"
#include "scene/core/SceneUtil.hpp"

#include <vector>

class BvhNode {
public:
    BvhNode(std::vector<Triangle>& triangles, int maxDepth, int minTriangles);
    ~BvhNode();

    // Triangle hit(const Ray&, float& t, float& u, float& v) const; // this is the preferred method, becuase it decouples ray tracing (triangle interpolation) logic from hit logic
    bool hit(const Ray& ray, TrianglePoint& triangle, float& t) const;
    void print() const;

private:
    Aabb boundingBox;

    BvhNode* left = nullptr;
    BvhNode* right = nullptr;

    std::vector<Triangle> triangles;





//delete the following after implementing the better version
public:
    BvhNode(std::vector<Mesh*> objects);//delete
private:
    Mesh* data = nullptr;//delete
    float sweepSurfaceAreaHeuristic(std::vector<Mesh*>& axisOrderedObjects, int i);//delete
};