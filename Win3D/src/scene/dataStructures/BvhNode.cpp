#include "scene/dataStructures/BvhNode.hpp"
#include "renderer/Ray.hpp"
#include "scene/core/SceneUtil.hpp"
#include "scene/dataStructures/Aabb.hpp"
#include "util/Util.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sys/types.h>
#include <vector>

static int sweepSurfaceAreaHeuristic(std::vector<Triangle>& tris, size_t start, size_t end);

#define MAX_DEPTH (10) // unused
#define MIN_TRIANGLES (2)

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

    root = new BvhNode(tris, 0, tris.size()-1);
}

BvhTree::~BvhTree() {
    delete root;
    root = nullptr;
}

// returns the closest triangle intersection
HitRecord BvhTree::intersect(const Ray& ray) const {
    constexpr double DOUBLE_MAX = std::numeric_limits<double>::max();

    // find all candidate triangles
    std::vector<Triangle> triangles{};
    root->intersect(ray, triangles);

    HitRecord record;
    record.t = DOUBLE_MAX;

    if (triangles.empty()) return record;

    // find the closest intersection
    for (Triangle& tri : triangles) {
        double u, v, t;
        t = mollerTrumboreIntersection(ray, Vector::asVec3(tri.v1.position), Vector::asVec3(tri.v2.position), Vector::asVec3(tri.v3.position), u, v);

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
            record.uv0[0] = tri.v1.u; record.uv0[1] = tri.v1.v;
            record.uv1[0] = tri.v2.u; record.uv1[1] = tri.v2.v;
            record.uv2[0] = tri.v3.u; record.uv2[1] = tri.v3.v;
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
double BvhTree::mollerTrumboreIntersection(const Ray& ray, const Vector& v0, const Vector& v1, const Vector& v2, double& u, double& v) {
    constexpr double epsilon = std::numeric_limits<double>::epsilon();

    Vector edge1 = v1 - v0;
    Vector edge2 = v2 - v0;

    Vector pvec = Vector::crossProduct(ray.direction, edge2);
    double det = Vector::dotProduct(edge1, pvec);

    // back face culling check - if winding order is opposite: if (det > -epsilon)
    if (det < epsilon)
        return -1;

    Vector tvec = ray.origin - v0;
    u = Vector::dotProduct(tvec, pvec);

    if (u < 0.0 || u > det)
        return -1;

    Vector qvec = Vector::crossProduct(tvec, edge1);
    v = Vector::dotProduct(ray.direction, qvec);

    if (v < 0.0 || u + v > det)
        return -1;

    double t = Vector::dotProduct(edge2, qvec);
    double invDet = 1.0 / det;
    t *= invDet;
    u *= invDet;
    v *= invDet;

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

    int splitIndex = (end-start) / 2;

    std::nth_element(tris.begin()+start, tris.begin()+splitIndex, tris.begin()+end, [axis](const Triangle& a, const Triangle& b) {
        return a.boundingBox.centroid()[axis] > b.boundingBox.centroid()[axis];
    });
    
    // step 3 - recurse
    left = new BvhNode(tris, start, start+splitIndex);
    right = new BvhNode(tris, start+splitIndex+1, end);
}

BvhNode::~BvhNode() {
    if (left) delete left;
    if (right) delete right;
    left = nullptr;
    right = nullptr;
}

void BvhNode::intersect(const Ray& ray, std::vector<Triangle>& tris) const {
    if (!boundingBox.intersect(ray))
        return;

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

int sweepSurfaceAreaHeuristic(std::vector<Triangle>& tris, size_t start, size_t end) {
    constexpr double MAX = std::numeric_limits<double>::max();
    
    float sahMin = MAX;
    int sahIndex = -1;

    // for each possible split index
    for (int i = start; i <= end; i++) {
        float lsa = 0, rsa = 0;
    
        for (int i = 0; i < sahIndex; i++) {
            lsa += tris[i].boundingBox.surfaceArea();
        }
        for (int i = sahIndex; i < tris.size(); i++) {
            rsa += tris[i].boundingBox.surfaceArea();
        }

        // calculate the surface area heuristic
        float sah = lsa * sahIndex + rsa * (tris.size()-sahIndex);

        // if better than previous
        if (sah < sahMin) {
            sahMin = sah;
            sahIndex = i;
        }
    }

    // return split index
    return sahIndex;
}