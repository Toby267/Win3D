#include "scene/dataStructures/BvhNode.hpp"
#include "renderer/Ray.hpp"
#include "scene/core/SceneUtil.hpp"
#include "scene/dataStructures/Aabb.hpp"
#include "util/Util.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <sys/types.h>
#include <vector>

#define MAX_DEPTH (10)
#define MIN_TRIANGLES (4)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * -------------------------------------------- [ BVH_TREE ] ------------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// default construction
BvhTree::BvhTree(std::vector<Triangle>& tris) {
    // can't assume that the bounding boxes have been calculated initially
    for (Triangle& t : tris) {
        t.boundingBox = Aabb();
        t.boundingBox.grow(t.v1.position);
        t.boundingBox.grow(t.v2.position);
        t.boundingBox.grow(t.v3.position);
    }

    // also delete this when fixed
    for (Triangle& t : tris) {
        boundingBox.grow(t.boundingBox);
    }

    root = new BvhNode(tris, 0, tris.size()-1);
}

BvhTree::~BvhTree() {
    delete root;
}

// returns the closest triangle intersection
HitRecord BvhTree::intersect(const Ray& ray) const {
    constexpr float FLOAT_MAX = std::numeric_limits<float>::max();

    if (!boundingBox.intersect(ray)) {
        HitRecord r;
        r.t = FLOAT_MAX;
        return r;
    }

    // find all candidate triangles
    std::vector<Triangle> triangles{};
    root->intersect(ray, triangles);

    HitRecord record;
    record.t = FLOAT_MAX;

    // find the closest intersection
    for (Triangle& tri : triangles) {
        float u, v, t;
        t = mollerTrumboreIntersection(ray, tri.v1.position.toVec3(), tri.v2.position.toVec3(), tri.v3.position.toVec3(), u, v);

        if (t != -1 && t < record.t) {
            record.u = u;
            record.v = v;
            record.t = t;
            // record.v1 = tri.v1;
            // record.v2 = tri.v2;
            // record.v3 = tri.v3;

            record.c0 = tri.v1.colour;
            record.c1 = tri.v2.colour;
            record.c2 = tri.v3.colour;
            record.n0 = tri.v1.normal;
            record.n1 = tri.v2.normal;
            record.n2 = tri.v3.normal;
            record.v0 = tri.v1.position;
            record.v1 = tri.v2.position;
            record.v2 = tri.v3.position;
        }
    }

    return record;
}

void BvhTree::print() const {
    root->print();
}

void BvhTree::printTriangleCount() const {
    std::cout << "triangle count: " << root->getTriangleCount() << '\n';
}

// determines whether a ray intersection a triangle, and at what u, v, & t values it occurs
// expects the vectors to be vec3
float BvhTree::mollerTrumboreIntersection(const Ray& ray, const Vector& v1, const Vector& v2, const Vector& v3, float& u, float& v) {
    constexpr float epsilon = std::numeric_limits<float>::epsilon();

    Vector edge1 = v2 - v1;
    Vector edge2 = v3 - v1;

    Vector pvec = Vector::crossProduct(ray.direction, edge2);
    float det = Vector::dotProduct(edge1, pvec);

    if (det > -epsilon && det < epsilon)
        return -1;

    float invDet = 1.0 / det;

    Vector tvec = ray.origin - v1;
    u = Vector::dotProduct(tvec, pvec) * invDet;

    if (u < 0.0 || u > 1.0)
        return -1;

    Vector qvec = Vector::crossProduct(tvec, edge1);
    v = Vector::dotProduct(ray.direction, qvec) * invDet;

    if (v < 0.0 || u + v > 1.0)
        return -1;

    float t = Vector::dotProduct(edge2, qvec) * invDet;

    return t;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * -------------------------------------------- [ BVH_NODE ] ------------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// recursively sets up the bvh hierarchy
BvhNode::BvhNode(std::vector<Triangle>& tris, size_t start, size_t end) {
    // step 0 - calculate containing bbox
    for (int i = start; i <= end; i++) {
        boundingBox.grow(tris[i].boundingBox);
    }
    
    // step 1 - stop recursing if minimal triangles is met - or splitting will result in a node with less than the minimal triangles
    int range = (end-start) + 1;
    if (range < 2 * MIN_TRIANGLES) {
        triangles.reserve(range);

        //store triangles for intersection
        for (int i = start; i <= end; i++)
            triangles.push_back(tris[i]);

        return;
    }

    // step 2 - calculate optimal split, then order triangles
    Vector span = boundingBox.max - boundingBox.min;
    short axis = 0;
    if (span.y() > span[axis]) axis = 1;
    if (span.z() > span[axis]) axis = 2;

    int splitIndex = (start+end) / 2;
    std::nth_element(tris.begin(), tris.begin() + splitIndex, tris.end(), [axis](const Triangle& a, const Triangle& b) {
        return a.boundingBox.centroid()[axis] > b.boundingBox.centroid()[axis];
    });

    // step 3 - recurse
    left = new BvhNode(tris, start, splitIndex);
    right = new BvhNode(tris, splitIndex+1, end);
}

BvhNode::~BvhNode() {
    if (left) delete left;
    if (right) delete right;
}

void BvhNode::intersect(const Ray& ray, std::vector<Triangle>& tris) const {
    // if (!boundingBox.intersect(ray))
        // return;
    
    // if leaf node
    if (!triangles.empty()) {
        tris.insert(tris.end(), triangles.begin(), triangles.end());
        return;
    }

    // if non-leaf node
    if (left) left->intersect(ray, tris);
    if (right) right->intersect(ray, tris);
}

void BvhNode::print() const {
    std::cout << "aabb: " << boundingBox.min << ", " << boundingBox.max << '\n';
    
    for (const Triangle& t : triangles)
        std::cout << "triangle\t";
    std::cout << '\n';
    
    if (left) left->print();
    if (right) right->print();
}

int BvhNode::getTriangleCount() const {
    int val = triangles.size();

    if (left) val += left->getTriangleCount();
    if (right) val += right->getTriangleCount();

    return val;
}

// float BvhNode::sweepSurfaceAreaHeuristic(std::vector<Mesh*>& objects, int index) {
    // return f(i) = LSA(i) * i + RSA(i) * (N-i)
// 
    // float lsa = 0, rsa = 0;
    // 
    // for (int i = 0; i < index; i++) {
        // lsa += objects[i]->calcBBox().surfaceArea();
    // }
    // for (int i = index; i < objects.size(); i++) {
        // rsa += objects[i]->calcBBox().surfaceArea();
    // }
// 
    // return lsa * index + rsa * (objects.size()-index);
// }