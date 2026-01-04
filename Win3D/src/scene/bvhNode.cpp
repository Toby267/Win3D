#include "scene/bvhNode.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

//for creating a leaf node - typically pass in a mesh
bvhNode::bvhNode(std::shared_ptr<Mesh> obj) {

}
bvhNode::bvhNode(std::vector<std::shared_ptr<Mesh>>& objects) {
    //is this a memory leak?
    *this = bvhNode(objects, 0, objects.size());
}
//for creating a bvhNode
bvhNode::bvhNode(std::vector<std::shared_ptr<Mesh>>& objects, int start, int end) {
    //surface area heuristic...
    //for now, don't split objects in two, later on you can


    /* pseudo code start */

    // if start - end == 2:
        // add leaf nodes and return
    // if start - end = 1:
        // add leaf node and return

    // for each axis x, y, z:
        // sort all objects by their position on said axis
        // find the index i that minimises sweepSurfaceAreaHeuristic();

    // choose the best split
    // split, and recurse

    /* pseudo code end */

    std::sort(objects.begin(), objects.end(), [](const std::shared_ptr<Mesh>& a, const std::shared_ptr<Mesh>& b){
        return a->getBBox().centroid().x() > b->getBBox().centroid().x();
    });

    int sahIndex = 0;
    float sahValue = sweepSurfaceAreaHeuristic(objects, 0);
    
    for (int i = 1; i < objects.size(); i++) {
        float val = sweepSurfaceAreaHeuristic(objects, i);
        if (val < sahValue) {
            sahIndex = i;
            sahValue = val;
        }
    }

    std::cout << sahValue << '\n';

    // left = std::make_unique<bvhNode>(objects, 0, sahIndex);
    // right = std::make_unique<bvhNode>(objects, sahIndex+1, objects.size());
}

bool bvhNode::hit(Ray& ray) const {
    if (!boundingBox.intersect(ray))
        return false;

    return left->hit(ray) || right->hit(ray);
}

aabb bvhNode::getBBox() const {
    return boundingBox;
}

float bvhNode::sweepSurfaceAreaHeuristic(std::vector<std::shared_ptr<Mesh>>& objects, int index) {
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