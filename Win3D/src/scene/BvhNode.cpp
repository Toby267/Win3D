#include "scene/BvhNode.hpp"
#include "scene/Aabb.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

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

   left = new BvhNode({objects.begin(), objects.begin()+sahIndex});
   right = new BvhNode({objects.begin()+sahIndex, objects.end()});
}

BvhNode::~BvhNode() {
    if (left) delete left;
    if (right) delete right;
    //this doesn't own the data, the scene class does
}

bool BvhNode::hit(Ray& ray) const {
    if (!boundingBox.intersect(ray))
        return false;

    return data && data->hit(ray) || left && left->hit(ray) || right && right->hit(ray);
}

void BvhNode::print() const {
    std::cout << "aabb: " << boundingBox.a << ", " << boundingBox.b << '\n';
    if (left != nullptr) left->print();
    if (right != nullptr) right->print();
}

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