#include "renderer/objects/bvhNode.hpp"
#include "renderer/objects/Object.hpp"

#include <algorithm>
#include <iostream>

//for creating a leaf node - typically pass in a mesh
bvhNode::bvhNode(std::shared_ptr<Object> obj) {

}
//for creating a bvhNode
bvhNode::bvhNode(std::vector<std::shared_ptr<Object>>& objects) {
    //surface area heuristic...
    //for now, don't split objects in two, later on you can


    //testing sah:
    std::cout << objects[0]->getBBox().surfaceArea() << "\n";

    return;

    // for each axis x, y, z:
        // sort all objects by their position on said axis
        // find the index i that minimises sweepSurfaceAreaHeuristic();

    // choose the best split
    // split, and recurse

    const int N = objects.size();
    
    std::sort(objects.begin(), objects.end(), [](const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b){
        return a->getBBox().centroid().x() > b->getBBox().centroid().x();
    });

    int sahIndex = 0;
    float sahValue = sweepSurfaceAreaHeuristic(objects, 0);
    
    for (int i = 1; i < N; i++) {
        float val = sweepSurfaceAreaHeuristic(objects, i);
        if (val > sahValue) {
            sahIndex = i;
            sahValue = val;
        }
    }


}

bool bvhNode::hit(Ray& ray) const {
    if (!boundingBox.intersect(ray))
        return false;

    return left->hit(ray) || right->hit(ray);
}

aabb bvhNode::getBBox() const {
    return boundingBox;
}

float bvhNode::sweepSurfaceAreaHeuristic(std::vector<std::shared_ptr<Object>>& objects, int index) {
    // return f(i) = LSA(i) * i + RSA(i) * (N-i)

    float lsa = 0, rsa = 0;
    
    for (int i = 0; i < index; i++) {
        lsa += objects[i]->getBBox().surfaceArea();
    }
    for (int i = index; i < objects.size(); i++) {
        rsa += objects[i]->getBBox().surfaceArea();
    }

    return lsa * index + rsa * (objects.size()-index);
}