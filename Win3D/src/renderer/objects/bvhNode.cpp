#include "renderer/objects/bvhNode.hpp"
#include "renderer/objects/Object.hpp"

//for creating a leaf node - typically pass in a mesh
bvhNode::bvhNode(std::shared_ptr<Object> obj) {

}
//for creating a bvhNode
bvhNode::bvhNode(std::vector<std::shared_ptr<Object>>& objects) {
    //surface area heuristic...
    //for now, don't split objects in two, later on you can

    // for each axis x, y, z:
        // sort all objects by their position on said axis
        // find the index i that minimises sweepSurfaceAreaHeuristic();

    // choose the best split
    // split, and recurse
}

bool bvhNode::hit(Ray& ray) const {
    if (!boundingBox.intersect(ray))
        return false;

    return left->hit(ray) || right->hit(ray);
}

float bvhNode::sweepSurfaceAreaHeuristic(std::shared_ptr<Object> objects, int i) {
    // return f(i) = LSA(i) * i + RSA(i) * (N-i)
}