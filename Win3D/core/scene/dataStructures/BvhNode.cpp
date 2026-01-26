#include "scene/dataStructures/BvhNode.hpp"
#include "scene/dataStructures/Aabb.hpp"
#include "util/Util.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BvhNode::BvhNode(std::vector<Triangle> tris) {
//     // step 1 - stop recursing if minimal triangles is met
//     if (tris.size() <= MIN_SIZE) {
//         for (int i = 0; i < tris.size(); i++) {
//             triangles[i] = tris[i];
//         }

//         boundingBox = Aabb(tris);

//         return;
//     }

//     // step 2 - work out best split, and split
//     boundingBox = objects[0]->calcBBox();
//     for (int i = 1; i < objects.size(); i++) {
//         boundingBox = Aabb(boundingBox, objects[i]->calcBBox());
//     }
// }


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
       boundingBox = Aabb(objects[0]->calcBBox(), objects[1]->calcBBox());
       return;
   }

   // step 2 - work out best split, and split
   boundingBox = objects[0]->calcBBox();
   for (int i = 1; i < objects.size(); i++) {
       boundingBox = Aabb(boundingBox, objects[i]->calcBBox());
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

BvhNode::~BvhNode() {
    if (left) delete left;
    if (right) delete right;
    //this doesn't own the data, the scene class does
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
    std::cout << "aabb: " << boundingBox.a << ", " << boundingBox.b << '\n';
    if (left != nullptr) left->print();
    if (right != nullptr) right->print();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ PRIVATE METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

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