#pragma once

#include "renderer/Ray.hpp"
#include "scene/dataStructures/Aabb.hpp"
#include "scene/core/SceneUtil.hpp"

#include <cstddef>
#include <vector>

class BvhNode {
public:
    static BvhNode* buildBvhTree(std::vector<Triangle>& triangles);
    ~BvhNode();

    int intersect(const Ray& ray, Triangle& triangle) const; //returns t
    void print() const;

private:
    BvhNode(std::vector<Triangle>& tris, size_t start, size_t end);

    Aabb boundingBox = Aabb();

    BvhNode* left = nullptr;
    BvhNode* right = nullptr;

    std::vector<Triangle> triangles;
};

class BvhTree {
public:
    BvhTree(std::vector<Triangle>& triangles);
    ~BvhTree();

    // finds all BvhNodes that the ray intersects with, determines which triangles of those nodes the ray intersects with (using moller trumbore),
    // then finds which is the closest triangle, adds its data to the HitRecord, and returns
    HitRecord intersect(const Ray& ray);

private:
    BvhNode* root = nullptr;
};
