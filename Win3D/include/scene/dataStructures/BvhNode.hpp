#pragma once

#include "scene/Mesh.hpp"
#include "scene/dataStructures/Aabb.hpp"
#include "scene/Util.hpp"
#include "util/Vector.hpp"

#include <vector>

#define MIN_SIZE 4

//why don't i make it so that each mesh has an accelerated data structure instead of the scene having one...

//has instance(s) of either left, right, left & right, or just data
//always has an aabb
class BvhNode {
private:
    Aabb boundingBox;

    BvhNode* left = nullptr;
    BvhNode* right = nullptr;

    Mesh* data = nullptr;

    //store copies of the meshes triangle(s) for this node
    // std::vector<Triangle> triangles;

public:
    //constructors/destructor
    BvhNode(std::vector<Mesh*> objects); //constructs a bvh tree on a mesh by mesh basis
    BvhNode(std::vector<Triangle> triangles); // constructs a bvh tree on a triangle by traingle basis 
    ~BvhNode();

    //public methods
    bool hit(const Ray& ray, TrianglePoint& triangle, float& t) const;
    void print() const;

private:
    //private methods
    float sweepSurfaceAreaHeuristic(std::vector<Mesh*>& axisOrderedObjects, int i);
};
