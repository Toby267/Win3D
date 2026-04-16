#pragma once

#include "util/Util.hpp"
#include "scene/core/SceneUtil.hpp"
#include "renderer/Ray.hpp"


// representing an axis alligned bounding box, and related functions
struct Aabb {
    Vector min = Vector::max();
    Vector max = Vector::min();

    // public methods
    void grow(Vector v);
    void grow(Aabb bbox);

    bool intersect(const Ray& ray) const;
    
    double surfaceArea() const;
    Vector centroid() const;

    // operator overloads
    friend std::ostream& operator<<(std::ostream& os, const Aabb& b);
};

// represents a triangle that is stored within a bvh node
struct Triangle {
    Vertex v1, v2, v3;
    Aabb boundingBox;
} typedef Triangle;
