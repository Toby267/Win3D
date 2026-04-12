#pragma once

#include "util/Util.hpp"
#include "scene/core/SceneUtil.hpp"
#include "renderer/Ray.hpp"

struct Aabb {
    Vector min = Vector::max();
    Vector max = Vector::min();

    //public methods
    void grow(Vector v);
    void grow(Aabb bbox);

    bool intersect(const Ray& ray) const;
    
    double surfaceArea() const;
    Vector centroid() const;

    friend std::ostream& operator<<(std::ostream& os, const Aabb& b);
};

struct Triangle {
    Vertex v1, v2, v3;
    Aabb boundingBox;
} typedef Triangle;