#include "scene/dataStructures/Aabb.hpp"
#include "renderer/Ray.hpp"
#include "util/Util.hpp"
#include <cassert>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Aabb::grow(Aabb bbox) {
    if (bbox.min.x() < min.x()) min.x() = bbox.min.x();
    if (bbox.min.y() < min.y()) min.y() = bbox.min.y();
    if (bbox.min.z() < min.z()) min.z() = bbox.min.z();

    if (bbox.max.x() > max.x()) max.x() = bbox.max.x();
    if (bbox.max.y() > max.y()) max.y() = bbox.max.y();
    if (bbox.max.z() > max.z()) max.z() = bbox.max.z();

    // min = min - Vector(1, 1, 1);
    // max = max + Vector(1, 1, 1);
}

void Aabb::grow(Vector v) {
    if (v.x() < min.x()) min.x() = v.x();
    if (v.y() < min.y()) min.y() = v.y();
    if (v.z() < min.z()) min.z() = v.z();

    if (v.x() > max.x()) max.x() = v.x();
    if (v.y() > max.y()) max.y() = v.y();
    if (v.z() > max.z()) max.z() = v.z();

    // min = min - Vector(1, 1, 1);
    // max = max + Vector(1, 1, 1);
}

bool Aabb::intersect(const Ray& ray) const {
    //calculate the t intervals
    Vector t0 = (min - ray.origin) / ray.direction;
    Vector t1 = (max - ray.origin) / ray.direction;

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

double Aabb::surfaceArea() const {
    Vector d = min-max;
    return 2 * (d.x() * d.y() + d.x() * d.z() + d.y() * d.z());
}

Vector Aabb::centroid() const {
    return (min + max) / 2;
}

std::ostream& operator<<(std::ostream& os, const Aabb& b) {
    os << "min: " << b.min << ", max: " << b.max;
    return os;
}