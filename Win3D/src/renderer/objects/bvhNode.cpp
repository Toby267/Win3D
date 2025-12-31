#include "renderer/objects/bvhNode.hpp"

//for creating a leaf node - typically pass in a mesh
bvhNode::bvhNode(std::shared_ptr<Object> obj) {

}
//for creating a bvhNode
bvhNode::bvhNode(std::vector<std::shared_ptr<Mesh>> objects) {

}

bool bvhNode::hit(Ray& ray) {

}