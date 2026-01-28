#pragma once

#include "renderer/Ray.hpp"
#include "scene/dataStructures/Aabb.hpp"

#include <cstddef>
#include <vector>

class BvhNode {
public:
    BvhNode(std::vector<Triangle>& tris, size_t start, size_t end);
    ~BvhNode();

    void intersect(const Ray& ray, std::vector<Triangle>& triangles) const;
    void print() const;
    int getTriangleCount() const;

private:
    Aabb boundingBox = Aabb();

    BvhNode* left = nullptr;
    BvhNode* right = nullptr;

    std::vector<Triangle> triangles;
};

class BvhTree {
public:
    BvhTree(std::vector<Triangle>& triangles);
    ~BvhTree();

    HitRecord intersect(const Ray& ray) const;
    void print() const;
    void printTriangleCount() const;

private:
    static double mollerTrumboreIntersection(const Ray& ray, const Vector& v1, const Vector& v2, const Vector& v3, double& u, double& v);

    BvhNode* root = nullptr;

    // Aabb boundingBox = Aabb();//delete this when got it working properly
};
