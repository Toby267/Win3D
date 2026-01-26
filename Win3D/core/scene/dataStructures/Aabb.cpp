#include "scene/dataStructures/Aabb.hpp"

#include "util/Util.hpp"
#include <cassert>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Aabb::Aabb(Vector min, Vector max): a(min), b(max) {
    assert(min.getLength() == 3 && max.getLength() == 3);
}

Aabb::Aabb(Aabb b1, Aabb b2) {
    a.x() = b1.a.x() < b2.a.x() ? b1.a.x() : b2.a.x();
    a.y() = b1.a.y() < b2.a.y() ? b1.a.y() : b2.a.y();
    a.z() = b1.a.z() < b2.a.z() ? b1.a.z() : b2.a.z();

    b.x() = b1.b.x() > b2.b.x() ? b1.b.x() : b2.b.x();
    b.y() = b1.b.y() > b2.b.y() ? b1.b.y() : b2.b.y();
    b.z() = b1.b.z() > b2.b.z() ? b1.b.z() : b2.b.z();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Aabb::intersect(const Ray& ray) const {
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

float Aabb::surfaceArea() const {
    Vector d = a-b;
    return 2 * (d.x() * d.y() + d.x() * d.z() + d.y() * d.z());
}

Vector Aabb::centroid() const {
    return (a + b) / 2;
}