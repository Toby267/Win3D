#pragma once

#include "Mesh.hpp"
#include "util/Vector.hpp"
#include "renderer/Ray.hpp"

class aabb {
private:
    Vector a;
    Vector b;

public:
    aabb(Vector min, Vector max);
    bool hit(const Ray& ray);
};

class bvhNode {
private:
    bvhNode* left = nullptr;
    bvhNode* right = nullptr;

    aabb boundingBox;

public:
    bvhNode(Mesh obj);//leaf
    bvhNode(Vector min, Vector max);

};
