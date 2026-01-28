#pragma once


#include "scene/dataStructures/Aabb.hpp"
#include "scene/objects/Mesh.hpp"


class BvhNodeOld {
    private:
    Aabb boundingBox;

    BvhNodeOld* left = nullptr;
    BvhNodeOld* right = nullptr;

    Mesh* data = nullptr;

public:
    //constructors/destructor
    BvhNodeOld(std::vector<Mesh*> objects); //constructs a bvh tree on a mesh by mesh basis
    BvhNodeOld(std::vector<Triangle> triangles); // constructs a bvh tree on a triangle by traingle basis 
    ~BvhNodeOld();

    //public methods
    bool hit(const Ray& ray, TrianglePoint& triangle, float& t) const;
    void print() const;

private:
    //private methods
    float sweepSurfaceAreaHeuristic(std::vector<Mesh*>& axisOrderedObjects, int i);
};