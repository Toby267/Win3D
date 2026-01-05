#include "scene/bvhNode.hpp"

#include <algorithm>
#include <vector>

bvhNode::bvhNode(std::vector<Mesh*> objects) {
    // step 1 - generate bbox for the objects
    boundingBox = objects[0]->calcBBox();
    for (int i = 1; i < objects.size(); i++) {
        boundingBox = aabb(boundingBox, objects[i]->calcBBox());
    }

    // step 2 - if is 1 or 2 objects create them manually then return
    if (objects.size() == 1) {
        data = objects[0];
        return;
    }
    else if (objects.size() == 2) {
        left = new bvhNode({objects[0]});
        right = new bvhNode({objects[1]});
        return;
    }

    // step 3 - work out best split, and split - currently bugged
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

    left = new bvhNode({objects.begin(), objects.begin()+sahIndex});
    right = new bvhNode({objects.begin()+sahIndex, objects.end()});
}

bvhNode::~bvhNode() {
    if (left) delete left;
    if (right) delete right;
    //this doesn't own the data, the scene class does
}

bool bvhNode::hit(Ray& ray) {
    if (!boundingBox.intersect(ray))
        return false;

    return left->hit(ray) || right->hit(ray);
}

float bvhNode::sweepSurfaceAreaHeuristic(std::vector<Mesh*>& objects, int index) {
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