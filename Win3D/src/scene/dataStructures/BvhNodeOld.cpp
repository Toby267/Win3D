#include "scene/dataStructures/Aabb.hpp"
#include "scene/objects/Mesh.hpp"
#include <algorithm>
#include "scene/dataStructures/BvhNodeOld.hpp"

BvhNodeOld::~BvhNodeOld() {
    if (left) delete left;
    if (right) delete right;
}

BvhNodeOld::BvhNodeOld(std::vector<Mesh*> objects) {
   // step 1 - if is 1 or 2 objects create them manually then return
   if (objects.size() == 1) {
       data = objects[0];
       boundingBox = objects[0]->calcBBox();
       return;
   }
   else if (objects.size() == 2) {
       left = new BvhNodeOld({objects[0]});
       right = new BvhNodeOld({objects[1]});
       boundingBox = Aabb(objects[0]->calcBBox());
       boundingBox.grow(objects[1]->calcBBox());
    //    boundingBox = Aabb(objects[0]->calcBBox(), objects[1]->calcBBox());
       return;
   }

   // step 2 - work out best split, and split
   boundingBox = objects[0]->calcBBox();
   for (int i = 1; i < objects.size(); i++) {
    //    boundingBox = Aabb(boundingBox, objects[i]->calcBBox());
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

   left = new BvhNodeOld(std::vector<Mesh*>{objects.begin(), objects.begin()+sahIndex});
   right = new BvhNodeOld(std::vector<Mesh*>{objects.begin()+sahIndex, objects.end()});
}

bool BvhNodeOld::hit(const Ray& ray, TrianglePoint& triangle, float& t) const {
    if (!boundingBox.intersect(ray))
        return false;

    // TODO: if it intersects two objects, there is a chance that it just returns the values for one of them
    return data && data->hit(ray, triangle, t) || left && left->hit(ray, triangle, t) || right && right->hit(ray, triangle, t);
}

float BvhNodeOld::sweepSurfaceAreaHeuristic(std::vector<Mesh*>& objects, int index) {
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