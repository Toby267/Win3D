#pragma once

#include "renderer/Ray.hpp"
#include "scene/dataStructures/Aabb.hpp"

#include <cstddef>
#include <vector>

/**
 * Class representing a single bounding volume hierarchy node
 *
 * Stores its containing aabb, and either pointers to its child nodes or triangles stored
 * Has funcitonality for intersection
 */
class BvhNode {
private:
    Aabb boundingBox = Aabb();

    BvhNode* left = nullptr;
    BvhNode* right = nullptr;

    std::vector<Triangle> triangles;

public:
    // constructors/destructor
    BvhNode(std::vector<Triangle>& tris, size_t start, size_t end);
    ~BvhNode();

    // public methods
    void intersect(const Ray& ray, std::vector<Triangle>& triangles) const;
};

// represents a whole bounding volume hierarchy tree
class BvhTree {
private:
    static double mollerTrumboreIntersection(const Ray& ray, const Vector& v1, const Vector& v2, const Vector& v3, double& u, double& v);

    BvhNode* root = nullptr;

public:
    // constructors/destructor
    BvhTree(std::vector<Triangle>& triangles);
    ~BvhTree();

    // public methods
    HitRecord intersect(const Ray& ray) const;
};
