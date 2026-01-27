#include "scene/dataStructures/BvhNode.hpp"
#include "scene/core/SceneUtil.hpp"
#include "scene/dataStructures/Aabb.hpp"
#include "util/Util.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <sys/types.h>
#include <vector>

#define MAX_DEPTH (10)
#define MIN_TRIANGLES (4)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

BvhNode* BvhNode::buildBvhTree(std::vector<Triangle>& tris) {
    // calculates the bounding box of each triangle
    for (Triangle& t : tris) {
        t.boundingBox = Aabb();
        t.boundingBox.grow(t.v1.position);
        t.boundingBox.grow(t.v2.position);
        t.boundingBox.grow(t.v3.position);
    }

    return new BvhNode(tris, 0, tris.size()-1);
}

/**
 * @param start - the index of the first triangle
 * @param end - the index of the last triangle
*/
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
            triangles.emplace_back(tris[i]);

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool BvhNode::hit(const Ray& ray, TrianglePoint& triangle, float& t) const {
    if (!boundingBox.intersect(ray))
        return false;

    // TODO: if it intersects two objects, there is a chance that it just returns the values for one of them
    return data && data->hit(ray, triangle, t) || left && left->hit(ray, triangle, t) || right && right->hit(ray, triangle, t);
}

void BvhNode::print() const {
    std::cout << "aabb: " << boundingBox.min << ", " << boundingBox.max << '\n';
    
    for (const Triangle& t : triangles)
        std::cout << "triangle\t";
    std::cout << '\n';
    
    if (left != nullptr) left->print();
    if (right != nullptr) right->print();
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

BvhNode::BvhNode(std::vector<Mesh*> objects) {
   // step 1 - if is 1 or 2 objects create them manually then return
   if (objects.size() == 1) {
       data = objects[0];
       boundingBox = objects[0]->calcBBox();
       return;
   }
   else if (objects.size() == 2) {
       left = new BvhNode({objects[0]});
       right = new BvhNode({objects[1]});
       boundingBox = objects[0]->calcBBox();
       boundingBox.grow(objects[1]->calcBBox());
       return;
   }

   // step 2 - work out best split, and split
   boundingBox = objects[0]->calcBBox();
   for (int i = 1; i < objects.size(); i++) {
       boundingBox.grow(objects[i]->calcBBox());
   }

   //TODO: this should by x, then y, then z to find the best split
   std::sort(objects.begin(), objects.end(), [](Mesh* a, Mesh* b) {
       return a->calcBBox().centroid().x() > b->calcBBox().centroid().x();
   });

   int sahIndex = 0;
   float sahValue = sweepSurfaceAreaHeuristic(objects, 0);
   for (int i = 0; i < objects.size(); i++) {        
       float val = sweepSurfaceAreaHeuristic(objects, i);
       if (val < sahValue) {
           sahIndex = i;
           sahValue = val;
       }
   }

   std::nth_element(objects.begin(), objects.begin() + sahIndex, objects.end(), [](Mesh* a, Mesh* b) {
       return a->calcBBox().centroid().x() > b->calcBBox().centroid().x();
   });

   left = new BvhNode(std::vector<Mesh*>{objects.begin(), objects.begin()+sahIndex});
   right = new BvhNode(std::vector<Mesh*>{objects.begin()+sahIndex, objects.end()});
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // * ---------------------------------------- [ PRIVATE METHODS ] ---------------------------------------- * //
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

float BvhNode::sweepSurfaceAreaHeuristic(std::vector<Mesh*>& objects, int index) {
    // return f(i) = LSA(i) * i + RSA(i) * (N-i)

    float lsa = 0, rsa = 0;
    
    for (int i = 0; i < index; i++) {
        lsa += objects[i]->calcBBox().surfaceArea();
    }
    for (int i = index; i < objects.size(); i++) {
        rsa += objects[i]->calcBBox().surfaceArea();
    }

    return lsa * index + rsa * (objects.size()-index);
}