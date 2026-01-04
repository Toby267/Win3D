#include "scene/aabb.hpp"
#include "util/Vector.hpp"
#include <cassert>

aabb::aabb(Vector min, Vector max): a(min), b(max) {
    assert(min.getLength() == 3 && max.getLength() == 3);
}

bool aabb::intersect(const Ray& ray) const{
    //calculate the t intervals
    Vector t0 = (a - ray.origin) / ray.direction;
    Vector t1 = (b - ray.origin) / ray.direction;

    //order the t intervals
    if (t0.x() > t1.x()) std::swap(t0.x(), t1.x());
    if (t0.y() > t1.y()) std::swap(t0.y(), t1.y());
    if (t0.z() > t1.z()) std::swap(t0.z(), t1.z());

    //if the intervals of x and y don't match, return false
    t0.x() = t0.x() > t0.y() ? t0.x() : t0.y();
    t1.x() = t1.x() < t1.y() ? t1.x() : t1.y();
    if (t1.x() <= t0.x()) return false;

    //if the intervals of x, y, and z don't match, return false
    t0.x() = t0.x() > t0.z() ? t0.x() : t0.z();
    t1.x() = t1.x() < t1.z() ? t1.x() : t1.z();
    if (t1.x() <= t0.x()) return false;

    //it is a hit
    return true;
}

float aabb::surfaceArea() {
    Vector d = a-b;
    return 2 * (d.x() * d.y() + d.x() * d.z() + d.y() * d.z());
}

Vector aabb::centroid() {
    return (a + b) / 2;
}