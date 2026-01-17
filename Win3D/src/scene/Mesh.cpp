#include "scene/Mesh.hpp"
#include "renderer/Ray.hpp"
#include "scene/Materials.hpp"
#include "util/Colour.hpp"
#include "util/Vector.hpp"

#include <iostream>
#include <limits>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mesh::Mesh(std::vector<Vector> v, std::vector<Colour> c, std::vector<Vector> t)
    : VERTICES_ORIGINAL(v), COLOURS_ORIGINAL(c), TRIANGLES_ORIGINAL(t), vertices(v), colours(c), triangles(t)
{

}
Mesh::Mesh(std::vector<Vector> v, std::vector<Colour> c, std::vector<Vector> t, std::vector<Vector> n)
    : VERTICES_ORIGINAL(v), COLOURS_ORIGINAL(c), TRIANGLES_ORIGINAL(t), NORMALS_ORIGINAL(n), vertices(v), colours(c), triangles(t), normals(n)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<Vector>& Mesh::getVertices() {
    return vertices;
}
std::vector<Colour>& Mesh::getColours() {
    return colours;
}
std::vector<Vector>& Mesh::getTriangles() {
    return triangles;
}

void Mesh::setScale(Matrix s) {
    scale = s;
    affineTransform = translation * rotation * scale;
}
void Mesh::setTranslation(Matrix t) {
    translation = t;
    affineTransform = translation * rotation * scale;
}
void Mesh::setRotation(Matrix r) {
    rotation = r;
    affineTransform = translation * rotation * scale;
}
void Mesh::setMaterial(Mat::Material m) {
    material = m;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Mesh::toWorldSpace() {
    for (Vector& vertex : vertices) {
        vertex = affineTransform * vertex;
    }
}
void Mesh::applyAffineTransform(Matrix m) {
    for (Vector& vertex : vertices) {
        vertex = m * vertex;
    }
}
void Mesh::applyTransform(Matrix m) {
    for (Vector& vertex : vertices) {
        vertex = m * vertex;
        vertex = vertex / vertex.w();
    }
}

void Mesh::reset() {
    vertices = VERTICES_ORIGINAL;
    colours = COLOURS_ORIGINAL;
    triangles = TRIANGLES_ORIGINAL;
}

void Mesh::clip() {
    double xMax = vertices[0].x(), yMax = vertices[0].y(), zMax = vertices[0].z();
    double xMin = vertices[0].x(), yMin = vertices[0].y(), zMin = vertices[0].z();

    for (Vector& vertex : vertices) {
        if (vertex.x() > xMax) xMax = vertex.x();
        if (vertex.y() > yMax) yMax = vertex.y();
        if (vertex.z() > zMax) zMax = vertex.z();

        if (vertex.x() < xMin) xMin = vertex.x();
        if (vertex.y() < yMin) yMin = vertex.y();
        if (vertex.z() < zMin) zMin = vertex.z();
    }

    if (xMin >  1 || yMin >  1 || zMin >  1) triangles.clear();
    if (xMax < -1 || yMax < -1 || zMax < -1) triangles.clear();
}

Aabb Mesh::calcBBox() const {
    constexpr float MIN = std::numeric_limits<float>::lowest();
    constexpr float MAX = std::numeric_limits<float>::max();
    
    Vector min(MAX, MAX, MAX);
    Vector max(MIN, MIN, MIN);

    for (Vector vertex : vertices) {
        if (vertex.x() > max.x()) max.x() = vertex.x();
        if (vertex.y() > max.y()) max.y() = vertex.y();
        if (vertex.z() > max.z()) max.z() = vertex.z();

        if (vertex.x() < min.x()) min.x() = vertex.x();
        if (vertex.y() < min.y()) min.y() = vertex.y();
        if (vertex.z() < min.z()) min.z() = vertex.z();
    }

    return Aabb(min, max);
}

bool Mesh::hit(const Ray& ray, TrianglePoint& triangle, float& t) const {
    for (const Vector& tri : triangles) {
        float u, v, tNew;
        bool hit = mollerTrumboreIntersection(ray, tri, u, v, tNew);

        // if hit and triangle is closer
        if (hit && tNew < t) {
            // update record
            t = tNew;

            triangle.mat = material;
            triangle.u = u;
            triangle.v = v;
            triangle.c0 = colours[tri[0]];
            triangle.c1 = colours[tri[1]];
            triangle.c2 = colours[tri[2]];
            triangle.n0 = normals[tri[0]];
            triangle.n1 = normals[tri[1]];
            triangle.n2 = normals[tri[2]];
            triangle.v0 = vertices[tri[0]];
            triangle.v1 = vertices[tri[1]];
            triangle.v2 = vertices[tri[2]];
        }
    }

    constexpr float FLOAT_MAX = std::numeric_limits<float>::max();
    return t != FLOAT_MAX;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ PRIVATE METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Mesh::mollerTrumboreIntersection(const Ray& ray, const Vector& triangle, float& u, float& v, float &t) const {
    constexpr float epsilon = std::numeric_limits<float>::epsilon();

    const Vector vert0 = Vector( vertices[triangle[0]].x(), vertices[triangle[0]].y(), vertices[triangle[0]].z() );
    const Vector vert1 = Vector( vertices[triangle[1]].x(), vertices[triangle[1]].y(), vertices[triangle[1]].z() );
    const Vector vert2 = Vector( vertices[triangle[2]].x(), vertices[triangle[2]].y(), vertices[triangle[2]].z() );

    Vector edge1 = vert1 - vert0;
    Vector edge2 = vert2 - vert0;

    Vector pvec = Vector::crossProduct(ray.direction, edge2);
    float det = Vector::dotProduct(edge1, pvec);

    if (det > -epsilon && det < epsilon)
        return false;

    float invDet = 1.0 / det;

    Vector tvec = ray.origin - vert0;
    u = Vector::dotProduct(tvec, pvec) * invDet;

    if (u < 0.0 || u > 1.0)
        return false;

    Vector qvec = Vector::crossProduct(tvec, edge1);
    v = Vector::dotProduct(ray.direction, qvec) * invDet;

    if (v < 0.0 || u + v > 1.0)
        return false;

    t = Vector::dotProduct(edge2, qvec) * invDet;

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * --------------------------------------- [ OPERATOR OVERLOADS ] -------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, const Mesh& obj) {
    os << "printing out object vertices:\n";
    for (const Vector& vertex : obj.vertices) {
        os << "vertex: " << vertex << '\n';
    }
    return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ STATIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mesh* Mesh::triangle() {
    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> triangles;

    vertices.emplace_back(-1, -1, -1, 1);
    vertices.emplace_back(0,  1, 1, 1);
    vertices.emplace_back( 1, -1, -1, 1);

    colours.emplace_back(Colour::red());
    colours.emplace_back(Colour::green());
    colours.emplace_back(Colour::blue());
    
    triangles.emplace_back(0, 1, 2);

    return new Mesh(vertices, colours, triangles);
}

Mesh* Mesh::cube() {
    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> triangles;
    std::vector<Vector> normals;

    vertices.emplace_back( 1.000000, 1.000000, -1.000000, 1 );
    vertices.emplace_back( 1.000000, -1.000000, -1.000000, 1 );
    vertices.emplace_back( 1.000000, 1.000000, 1.000000, 1 );
    vertices.emplace_back( 1.000000, -1.000000, 1.000000, 1 );
    vertices.emplace_back( -1.000000, 1.000000, -1.000000, 1 );
    vertices.emplace_back( -1.000000, -1.000000, -1.000000, 1 );
    vertices.emplace_back( -1.000000, 1.000000, 1.000000, 1 );
    vertices.emplace_back( -1.000000, -1.000000, 1.000000, 1 );

    colours.emplace_back(Colour::red());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::green());
    
    normals.emplace_back( 0.5774, 0.5773, -0.5773 );
    normals.emplace_back( 0.5773, -0.5774, -0.5774 );
    normals.emplace_back( 0.5773, 0.5774, 0.5774 );
    normals.emplace_back( 0.5774, -0.5773, 0.5773 );
    normals.emplace_back( -0.5773, 0.5774, -0.5774 );
    normals.emplace_back( -0.5774, -0.5773, -0.5773 );
    normals.emplace_back( -0.5774, 0.5773, 0.5773 );
    normals.emplace_back( -0.5773, -0.5774, 0.5774 );
    
    triangles.emplace_back( 5, 3, 1 );
    triangles.emplace_back( 3, 8, 4 );
    triangles.emplace_back( 7, 6, 8 );
    triangles.emplace_back( 2, 8, 6 );
    triangles.emplace_back( 1, 4, 2 );
    triangles.emplace_back( 5, 2, 6 );
    triangles.emplace_back( 5, 7, 3 );
    triangles.emplace_back( 3, 7, 8 );
    triangles.emplace_back( 7, 5, 6 );
    triangles.emplace_back( 2, 4, 8 );
    triangles.emplace_back( 1, 3, 4 );
    triangles.emplace_back( 5, 1, 2 );

    for (Vector& i : triangles)
        i = i + Vector(-1, -1, -1);
    

    return new Mesh(vertices, colours, triangles, normals);
}
    
Mesh* Mesh::sphere() {
    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> triangles;
    std::vector<Vector> normals;

    vertices.emplace_back( 0.000000, -1.000000, 0.000000, 1 );
    vertices.emplace_back( 0.723607, -0.447220, 0.525725, 1 );
    vertices.emplace_back( -0.276388, -0.447220, 0.850649, 1 );
    vertices.emplace_back( -0.894426, -0.447216, 0.000000, 1 );
    vertices.emplace_back( -0.276388, -0.447220, -0.850649, 1 );
    vertices.emplace_back( 0.723607, -0.447220, -0.525725, 1 );
    vertices.emplace_back( 0.276388, 0.447220, 0.850649, 1 );
    vertices.emplace_back( -0.723607, 0.447220, 0.525725, 1 );
    vertices.emplace_back( -0.723607, 0.447220, -0.525725, 1 );
    vertices.emplace_back( 0.276388, 0.447220, -0.850649, 1 );
    vertices.emplace_back( 0.894426, 0.447216, 0.000000, 1 );
    vertices.emplace_back( 0.000000, 1.000000, 0.000000, 1 );
    vertices.emplace_back( -0.232822, -0.657519, 0.716563, 1 );
    vertices.emplace_back( -0.162456, -0.850654, 0.499995, 1 );
    vertices.emplace_back( -0.077607, -0.967950, 0.238853, 1 );
    vertices.emplace_back( 0.203181, -0.967950, 0.147618, 1 );
    vertices.emplace_back( 0.425323, -0.850654, 0.309011, 1 );
    vertices.emplace_back( 0.609547, -0.657519, 0.442856, 1 );
    vertices.emplace_back( 0.531941, -0.502302, 0.681712, 1 );
    vertices.emplace_back( 0.262869, -0.525738, 0.809012, 1 );
    vertices.emplace_back( -0.029639, -0.502302, 0.864184, 1 );
    vertices.emplace_back( 0.812729, -0.502301, -0.295238, 1 );
    vertices.emplace_back( 0.850648, -0.525736, 0.000000, 1 );
    vertices.emplace_back( 0.812729, -0.502301, 0.295238, 1 );
    vertices.emplace_back( 0.203181, -0.967950, -0.147618, 1 );
    vertices.emplace_back( 0.425323, -0.850654, -0.309011, 1 );
    vertices.emplace_back( 0.609547, -0.657519, -0.442856, 1 );
    vertices.emplace_back( -0.753442, -0.657515, 0.000000, 1 );
    vertices.emplace_back( -0.525730, -0.850652, 0.000000, 1 );
    vertices.emplace_back( -0.251147, -0.967949, 0.000000, 1 );
    vertices.emplace_back( -0.483971, -0.502302, 0.716565, 1 );
    vertices.emplace_back( -0.688189, -0.525736, 0.499997, 1 );
    vertices.emplace_back( -0.831051, -0.502299, 0.238853, 1 );
    vertices.emplace_back( -0.232822, -0.657519, -0.716563, 1 );
    vertices.emplace_back( -0.162456, -0.850654, -0.499995, 1 );
    vertices.emplace_back( -0.077607, -0.967950, -0.238853, 1 );
    vertices.emplace_back( -0.831051, -0.502299, -0.238853, 1 );
    vertices.emplace_back( -0.688189, -0.525736, -0.499997, 1 );
    vertices.emplace_back( -0.483971, -0.502302, -0.716565, 1 );
    vertices.emplace_back( -0.029639, -0.502302, -0.864184, 1 );
    vertices.emplace_back( 0.262869, -0.525738, -0.809012, 1 );
    vertices.emplace_back( 0.531941, -0.502302, -0.681712, 1 );
    vertices.emplace_back( 0.956626, 0.251149, 0.147618, 1 );
    vertices.emplace_back( 0.951058, -0.000000, 0.309013, 1 );
    vertices.emplace_back( 0.860698, -0.251151, 0.442858, 1 );
    vertices.emplace_back( 0.860698, -0.251151, -0.442858, 1 );
    vertices.emplace_back( 0.951058, 0.000000, -0.309013, 1 );
    vertices.emplace_back( 0.956626, 0.251149, -0.147618, 1 );
    vertices.emplace_back( 0.155215, 0.251152, 0.955422, 1 );
    vertices.emplace_back( 0.000000, -0.000000, 1.000000, 1 );
    vertices.emplace_back( -0.155215, -0.251152, 0.955422, 1 );
    vertices.emplace_back( 0.687159, -0.251152, 0.681715, 1 );
    vertices.emplace_back( 0.587786, 0.000000, 0.809017, 1 );
    vertices.emplace_back( 0.436007, 0.251152, 0.864188, 1 );
    vertices.emplace_back( -0.860698, 0.251151, 0.442858, 1 );
    vertices.emplace_back( -0.951058, -0.000000, 0.309013, 1 );
    vertices.emplace_back( -0.956626, -0.251149, 0.147618, 1 );
    vertices.emplace_back( -0.436007, -0.251152, 0.864188, 1 );
    vertices.emplace_back( -0.587786, 0.000000, 0.809017, 1 );
    vertices.emplace_back( -0.687159, 0.251152, 0.681715, 1 );
    vertices.emplace_back( -0.687159, 0.251152, -0.681715, 1 );
    vertices.emplace_back( -0.587786, -0.000000, -0.809017, 1 );
    vertices.emplace_back( -0.436007, -0.251152, -0.864188, 1 );
    vertices.emplace_back( -0.956626, -0.251149, -0.147618, 1 );
    vertices.emplace_back( -0.951058, 0.000000, -0.309013, 1 );
    vertices.emplace_back( -0.860698, 0.251151, -0.442858, 1 );
    vertices.emplace_back( 0.436007, 0.251152, -0.864188, 1 );
    vertices.emplace_back( 0.587786, -0.000000, -0.809017, 1 );
    vertices.emplace_back( 0.687159, -0.251152, -0.681715, 1 );
    vertices.emplace_back( -0.155215, -0.251152, -0.955422, 1 );
    vertices.emplace_back( 0.000000, 0.000000, -1.000000, 1 );
    vertices.emplace_back( 0.155215, 0.251152, -0.955422, 1 );
    vertices.emplace_back( 0.831051, 0.502299, 0.238853, 1 );
    vertices.emplace_back( 0.688189, 0.525736, 0.499997, 1 );
    vertices.emplace_back( 0.483971, 0.502302, 0.716565, 1 );
    vertices.emplace_back( 0.029639, 0.502302, 0.864184, 1 );
    vertices.emplace_back( -0.262869, 0.525738, 0.809012, 1 );
    vertices.emplace_back( -0.531941, 0.502302, 0.681712, 1 );
    vertices.emplace_back( -0.812729, 0.502301, 0.295238, 1 );
    vertices.emplace_back( -0.850648, 0.525736, 0.000000, 1 );
    vertices.emplace_back( -0.812729, 0.502301, -0.295238, 1 );
    vertices.emplace_back( -0.531941, 0.502302, -0.681712, 1 );
    vertices.emplace_back( -0.262869, 0.525738, -0.809012, 1 );
    vertices.emplace_back( 0.029639, 0.502302, -0.864184, 1 );
    vertices.emplace_back( 0.483971, 0.502302, -0.716565, 1 );
    vertices.emplace_back( 0.688189, 0.525736, -0.499997, 1 );
    vertices.emplace_back( 0.831051, 0.502299, -0.238853, 1 );
    vertices.emplace_back( 0.077607, 0.967950, 0.238853, 1 );
    vertices.emplace_back( 0.162456, 0.850654, 0.499995, 1 );
    vertices.emplace_back( 0.232822, 0.657519, 0.716563, 1 );
    vertices.emplace_back( 0.753442, 0.657515, 0.000000, 1 );
    vertices.emplace_back( 0.525730, 0.850652, 0.000000, 1 );
    vertices.emplace_back( 0.251147, 0.967949, 0.000000, 1 );
    vertices.emplace_back( -0.203181, 0.967950, 0.147618, 1 );
    vertices.emplace_back( -0.425323, 0.850654, 0.309011, 1 );
    vertices.emplace_back( -0.609547, 0.657519, 0.442856, 1 );
    vertices.emplace_back( -0.203181, 0.967950, -0.147618, 1 );
    vertices.emplace_back( -0.425323, 0.850654, -0.309011, 1 );
    vertices.emplace_back( -0.609547, 0.657519, -0.442856, 1 );
    vertices.emplace_back( 0.077607, 0.967950, -0.238853, 1 );
    vertices.emplace_back( 0.162456, 0.850654, -0.499995, 1 );
    vertices.emplace_back( 0.232822, 0.657519, -0.716563, 1 );
    vertices.emplace_back( 0.361800, 0.894429, -0.262863, 1 );
    vertices.emplace_back( 0.638194, 0.723610, -0.262864, 1 );
    vertices.emplace_back( 0.447209, 0.723612, -0.525728, 1 );
    vertices.emplace_back( -0.138197, 0.894430, -0.425319, 1 );
    vertices.emplace_back( -0.052790, 0.723612, -0.688185, 1 );
    vertices.emplace_back( -0.361804, 0.723612, -0.587778, 1 );
    vertices.emplace_back( -0.447210, 0.894429, 0.000000, 1 );
    vertices.emplace_back( -0.670817, 0.723611, -0.162457, 1 );
    vertices.emplace_back( -0.670817, 0.723611, 0.162457, 1 );
    vertices.emplace_back( -0.138197, 0.894430, 0.425319, 1 );
    vertices.emplace_back( -0.361804, 0.723612, 0.587778, 1 );
    vertices.emplace_back( -0.052790, 0.723612, 0.688185, 1 );
    vertices.emplace_back( 0.361800, 0.894429, 0.262863, 1 );
    vertices.emplace_back( 0.447209, 0.723612, 0.525728, 1 );
    vertices.emplace_back( 0.638194, 0.723610, 0.262864, 1 );
    vertices.emplace_back( 0.861804, 0.276396, -0.425322, 1 );
    vertices.emplace_back( 0.809019, 0.000000, -0.587782, 1 );
    vertices.emplace_back( 0.670821, 0.276397, -0.688189, 1 );
    vertices.emplace_back( -0.138199, 0.276397, -0.951055, 1 );
    vertices.emplace_back( -0.309016, -0.000000, -0.951057, 1 );
    vertices.emplace_back( -0.447215, 0.276397, -0.850649, 1 );
    vertices.emplace_back( -0.947213, 0.276396, -0.162458, 1 );
    vertices.emplace_back( -1.000000, 0.000001, 0.000000, 1 );
    vertices.emplace_back( -0.947213, 0.276397, 0.162458, 1 );
    vertices.emplace_back( -0.447216, 0.276397, 0.850648, 1 );
    vertices.emplace_back( -0.309017, -0.000001, 0.951056, 1 );
    vertices.emplace_back( -0.138199, 0.276397, 0.951055, 1 );
    vertices.emplace_back( 0.670820, 0.276396, 0.688190, 1 );
    vertices.emplace_back( 0.809019, -0.000002, 0.587783, 1 );
    vertices.emplace_back( 0.861804, 0.276394, 0.425323, 1 );
    vertices.emplace_back( 0.309017, -0.000000, -0.951056, 1 );
    vertices.emplace_back( 0.447216, -0.276398, -0.850648, 1 );
    vertices.emplace_back( 0.138199, -0.276398, -0.951055, 1 );
    vertices.emplace_back( -0.809018, -0.000000, -0.587783, 1 );
    vertices.emplace_back( -0.670819, -0.276397, -0.688191, 1 );
    vertices.emplace_back( -0.861803, -0.276396, -0.425324, 1 );
    vertices.emplace_back( -0.809018, 0.000000, 0.587783, 1 );
    vertices.emplace_back( -0.861803, -0.276396, 0.425324, 1 );
    vertices.emplace_back( -0.670819, -0.276397, 0.688191, 1 );
    vertices.emplace_back( 0.309017, 0.000000, 0.951056, 1 );
    vertices.emplace_back( 0.138199, -0.276398, 0.951055, 1 );
    vertices.emplace_back( 0.447216, -0.276398, 0.850648, 1 );
    vertices.emplace_back( 1.000000, 0.000000, 0.000000, 1 );
    vertices.emplace_back( 0.947213, -0.276396, 0.162458, 1 );
    vertices.emplace_back( 0.947213, -0.276396, -0.162458, 1 );
    vertices.emplace_back( 0.361803, -0.723612, -0.587779, 1 );
    vertices.emplace_back( 0.138197, -0.894429, -0.425321, 1 );
    vertices.emplace_back( 0.052789, -0.723611, -0.688186, 1 );
    vertices.emplace_back( -0.447211, -0.723612, -0.525727, 1 );
    vertices.emplace_back( -0.361801, -0.894429, -0.262863, 1 );
    vertices.emplace_back( -0.638195, -0.723609, -0.262863, 1 );
    vertices.emplace_back( -0.638195, -0.723609, 0.262864, 1 );
    vertices.emplace_back( -0.361801, -0.894428, 0.262864, 1 );
    vertices.emplace_back( -0.447211, -0.723610, 0.525729, 1 );
    vertices.emplace_back( 0.670817, -0.723611, -0.162457, 1 );
    vertices.emplace_back( 0.670818, -0.723610, 0.162458, 1 );
    vertices.emplace_back( 0.447211, -0.894428, 0.000001, 1 );
    vertices.emplace_back( 0.052790, -0.723612, 0.688185, 1 );
    vertices.emplace_back( 0.138199, -0.894429, 0.425321, 1 );
    vertices.emplace_back( 0.361805, -0.723611, 0.587779, 1 );

    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());

    normals.emplace_back( -0.0000, -1.0000, -0.0000 );
    normals.emplace_back( 0.7236, -0.4472, 0.5257 );
    normals.emplace_back( -0.2764, -0.4472, 0.8506 );
    normals.emplace_back( -0.8944, -0.4472, -0.0000 );
    normals.emplace_back( -0.2764, -0.4472, -0.8506 );
    normals.emplace_back( 0.7236, -0.4472, -0.5257 );
    normals.emplace_back( 0.2764, 0.4472, 0.8506 );
    normals.emplace_back( -0.7236, 0.4472, 0.5257 );
    normals.emplace_back( -0.7236, 0.4472, -0.5257 );
    normals.emplace_back( 0.2764, 0.4472, -0.8506 );
    normals.emplace_back( 0.8944, 0.4472, -0.0000 );
    normals.emplace_back( -0.0000, 1.0000, -0.0000 );
    normals.emplace_back( -0.2308, -0.6650, 0.7103 );
    normals.emplace_back( -0.1625, -0.8507, 0.5000 );
    normals.emplace_back( -0.0806, -0.9654, 0.2480 );
    normals.emplace_back( 0.2110, -0.9654, 0.1533 );
    normals.emplace_back( 0.4253, -0.8507, 0.3090 );
    normals.emplace_back( 0.6042, -0.6650, 0.4390 );
    normals.emplace_back( 0.5237, -0.5038, 0.6870 );
    normals.emplace_back( 0.2629, -0.5257, 0.8090 );
    normals.emplace_back( -0.0198, -0.5038, 0.8636 );
    normals.emplace_back( 0.8152, -0.5038, -0.2857 );
    normals.emplace_back( 0.8506, -0.5257, -0.0000 );
    normals.emplace_back( 0.8152, -0.5038, 0.2857 );
    normals.emplace_back( 0.2110, -0.9654, -0.1533 );
    normals.emplace_back( 0.4253, -0.8507, -0.3090 );
    normals.emplace_back( 0.6042, -0.6650, -0.4390 );
    normals.emplace_back( -0.7469, -0.6650, -0.0000 );
    normals.emplace_back( -0.5257, -0.8507, -0.0000 );
    normals.emplace_back( -0.2608, -0.9654, -0.0000 );
    normals.emplace_back( -0.4915, -0.5038, 0.7103 );
    normals.emplace_back( -0.6882, -0.5257, 0.5000 );
    normals.emplace_back( -0.8274, -0.5038, 0.2480 );
    normals.emplace_back( -0.2308, -0.6650, -0.7103 );
    normals.emplace_back( -0.1625, -0.8507, -0.5000 );
    normals.emplace_back( -0.0806, -0.9654, -0.2480 );
    normals.emplace_back( -0.8274, -0.5038, -0.2480 );
    normals.emplace_back( -0.6882, -0.5257, -0.5000 );
    normals.emplace_back( -0.4915, -0.5038, -0.7103 );
    normals.emplace_back( -0.0198, -0.5038, -0.8636 );
    normals.emplace_back( 0.2629, -0.5257, -0.8090 );
    normals.emplace_back( 0.5237, -0.5038, -0.6870 );
    normals.emplace_back( 0.9578, 0.2431, 0.1533 );
    normals.emplace_back( 0.9511, -0.0000, 0.3090 );
    normals.emplace_back( 0.8650, -0.2431, 0.4390 );
    normals.emplace_back( 0.8650, -0.2431, -0.4390 );
    normals.emplace_back( 0.9511, -0.0000, -0.3090 );
    normals.emplace_back( 0.9578, 0.2431, -0.1533 );
    normals.emplace_back( 0.1502, 0.2431, 0.9583 );
    normals.emplace_back( -0.0000, -0.0000, 1.0000 );
    normals.emplace_back( -0.1502, -0.2431, 0.9583 );
    normals.emplace_back( 0.6848, -0.2431, 0.6870 );
    normals.emplace_back( 0.5878, -0.0000, 0.8090 );
    normals.emplace_back( 0.4417, 0.2431, 0.8636 );
    normals.emplace_back( -0.8650, 0.2431, 0.4390 );
    normals.emplace_back( -0.9511, -0.0000, 0.3090 );
    normals.emplace_back( -0.9578, -0.2431, 0.1533 );
    normals.emplace_back( -0.4417, -0.2431, 0.8636 );
    normals.emplace_back( -0.5878, -0.0000, 0.8090 );
    normals.emplace_back( -0.6848, 0.2431, 0.6870 );
    normals.emplace_back( -0.6848, 0.2431, -0.6870 );
    normals.emplace_back( -0.5878, -0.0000, -0.8090 );
    normals.emplace_back( -0.4417, -0.2431, -0.8636 );
    normals.emplace_back( -0.9578, -0.2431, -0.1533 );
    normals.emplace_back( -0.9511, -0.0000, -0.3090 );
    normals.emplace_back( -0.8650, 0.2431, -0.4390 );
    normals.emplace_back( 0.4417, 0.2431, -0.8636 );
    normals.emplace_back( 0.5878, -0.0000, -0.8090 );
    normals.emplace_back( 0.6848, -0.2431, -0.6870 );
    normals.emplace_back( -0.1502, -0.2431, -0.9583 );
    normals.emplace_back( -0.0000, -0.0000, -1.0000 );
    normals.emplace_back( 0.1502, 0.2431, -0.9583 );
    normals.emplace_back( 0.8274, 0.5038, 0.2480 );
    normals.emplace_back( 0.6882, 0.5257, 0.5000 );
    normals.emplace_back( 0.4915, 0.5038, 0.7103 );
    normals.emplace_back( 0.0198, 0.5038, 0.8636 );
    normals.emplace_back( -0.2629, 0.5257, 0.8090 );
    normals.emplace_back( -0.5237, 0.5038, 0.6870 );
    normals.emplace_back( -0.8152, 0.5038, 0.2857 );
    normals.emplace_back( -0.8506, 0.5257, -0.0000 );
    normals.emplace_back( -0.8152, 0.5038, -0.2857 );
    normals.emplace_back( -0.5237, 0.5038, -0.6870 );
    normals.emplace_back( -0.2629, 0.5257, -0.8090 );
    normals.emplace_back( 0.0198, 0.5038, -0.8636 );
    normals.emplace_back( 0.4915, 0.5038, -0.7103 );
    normals.emplace_back( 0.6882, 0.5257, -0.5000 );
    normals.emplace_back( 0.8274, 0.5038, -0.2480 );
    normals.emplace_back( 0.0806, 0.9654, 0.2480 );
    normals.emplace_back( 0.1625, 0.8507, 0.5000 );
    normals.emplace_back( 0.2308, 0.6650, 0.7103 );
    normals.emplace_back( 0.7469, 0.6650, -0.0000 );
    normals.emplace_back( 0.5257, 0.8507, -0.0000 );
    normals.emplace_back( 0.2607, 0.9654, -0.0000 );
    normals.emplace_back( -0.2110, 0.9654, 0.1533 );
    normals.emplace_back( -0.4253, 0.8507, 0.3090 );
    normals.emplace_back( -0.6042, 0.6650, 0.4390 );
    normals.emplace_back( -0.2110, 0.9654, -0.1533 );
    normals.emplace_back( -0.4253, 0.8507, -0.3090 );
    normals.emplace_back( -0.6042, 0.6650, -0.4390 );
    normals.emplace_back( 0.0806, 0.9654, -0.2480 );
    normals.emplace_back( 0.1625, 0.8507, -0.5000 );
    normals.emplace_back( 0.2308, 0.6650, -0.7103 );
    normals.emplace_back( 0.3682, 0.8904, -0.2675 );
    normals.emplace_back( 0.6317, 0.7275, -0.2675 );
    normals.emplace_back( 0.4496, 0.7276, -0.5182 );
    normals.emplace_back( -0.1406, 0.8904, -0.4329 );
    normals.emplace_back( -0.0592, 0.7276, -0.6835 );
    normals.emplace_back( -0.3539, 0.7276, -0.5878 );
    normals.emplace_back( -0.4551, 0.8904, -0.0000 );
    normals.emplace_back( -0.6683, 0.7276, -0.1549 );
    normals.emplace_back( -0.6683, 0.7276, 0.1549 );
    normals.emplace_back( -0.1406, 0.8904, 0.4329 );
    normals.emplace_back( -0.3539, 0.7276, 0.5878 );
    normals.emplace_back( -0.0592, 0.7276, 0.6835 );
    normals.emplace_back( 0.3682, 0.8904, 0.2675 );
    normals.emplace_back( 0.4496, 0.7276, 0.5182 );
    normals.emplace_back( 0.6317, 0.7275, 0.2675 );
    normals.emplace_back( 0.8593, 0.2724, -0.4329 );
    normals.emplace_back( 0.8090, 0.0089, -0.5878 );
    normals.emplace_back( 0.6772, 0.2724, -0.6835 );
    normals.emplace_back( -0.1461, 0.2724, -0.9510 );
    normals.emplace_back( -0.3090, 0.0089, -0.9510 );
    normals.emplace_back( -0.4408, 0.2724, -0.8553 );
    normals.emplace_back( -0.9496, 0.2724, -0.1549 );
    normals.emplace_back( -1.0000, 0.0089, -0.0000 );
    normals.emplace_back( -0.9496, 0.2724, 0.1549 );
    normals.emplace_back( -0.4408, 0.2724, 0.8553 );
    normals.emplace_back( -0.3090, 0.0089, 0.9510 );
    normals.emplace_back( -0.1461, 0.2724, 0.9510 );
    normals.emplace_back( 0.6772, 0.2724, 0.6835 );
    normals.emplace_back( 0.8090, 0.0089, 0.5878 );
    normals.emplace_back( 0.8593, 0.2724, 0.4329 );
    normals.emplace_back( 0.3090, -0.0089, -0.9510 );
    normals.emplace_back( 0.4408, -0.2724, -0.8553 );
    normals.emplace_back( 0.1461, -0.2724, -0.9510 );
    normals.emplace_back( -0.8090, -0.0089, -0.5878 );
    normals.emplace_back( -0.6772, -0.2724, -0.6835 );
    normals.emplace_back( -0.8593, -0.2724, -0.4329 );
    normals.emplace_back( -0.8090, -0.0089, 0.5878 );
    normals.emplace_back( -0.8593, -0.2724, 0.4329 );
    normals.emplace_back( -0.6772, -0.2724, 0.6835 );
    normals.emplace_back( 0.3090, -0.0089, 0.9510 );
    normals.emplace_back( 0.1461, -0.2724, 0.9510 );
    normals.emplace_back( 0.4408, -0.2724, 0.8553 );
    normals.emplace_back( 1.0000, -0.0089, -0.0000 );
    normals.emplace_back( 0.9496, -0.2724, 0.1549 );
    normals.emplace_back( 0.9496, -0.2724, -0.1549 );
    normals.emplace_back( 0.3539, -0.7276, -0.5878 );
    normals.emplace_back( 0.1406, -0.8904, -0.4329 );
    normals.emplace_back( 0.0592, -0.7276, -0.6835 );
    normals.emplace_back( -0.4496, -0.7276, -0.5182 );
    normals.emplace_back( -0.3682, -0.8904, -0.2675 );
    normals.emplace_back( -0.6317, -0.7275, -0.2675 );
    normals.emplace_back( -0.6317, -0.7275, 0.2675 );
    normals.emplace_back( -0.3682, -0.8904, 0.2675 );
    normals.emplace_back( -0.4496, -0.7275, 0.5182 );
    normals.emplace_back( 0.6683, -0.7275, -0.1549 );
    normals.emplace_back( 0.6683, -0.7275, 0.1549 );
    normals.emplace_back( 0.4551, -0.8904, -0.0000 );
    normals.emplace_back( 0.0592, -0.7276, 0.6835 );
    normals.emplace_back( 0.1406, -0.8904, 0.4329 );
    normals.emplace_back( 0.3539, -0.7276, 0.5878 );

    triangles.emplace_back( 1, 16, 15 );
    triangles.emplace_back( 2, 18, 24 );
    triangles.emplace_back( 1, 15, 30 );
    triangles.emplace_back( 1, 30, 36 );
    triangles.emplace_back( 1, 36, 25 );
    triangles.emplace_back( 2, 24, 45 );
    triangles.emplace_back( 3, 21, 51 );
    triangles.emplace_back( 4, 33, 57 );
    triangles.emplace_back( 5, 39, 63 );
    triangles.emplace_back( 6, 42, 69 );
    triangles.emplace_back( 2, 45, 52 );
    triangles.emplace_back( 3, 51, 58 );
    triangles.emplace_back( 4, 57, 64 );
    triangles.emplace_back( 5, 63, 70 );
    triangles.emplace_back( 6, 69, 46 );
    triangles.emplace_back( 7, 75, 90 );
    triangles.emplace_back( 8, 78, 96 );
    triangles.emplace_back( 9, 81, 99 );
    triangles.emplace_back( 10, 84, 102 );
    triangles.emplace_back( 11, 87, 91 );
    triangles.emplace_back( 93, 100, 12 );
    triangles.emplace_back( 92, 103, 93 );
    triangles.emplace_back( 91, 104, 92 );
    triangles.emplace_back( 93, 103, 100 );
    triangles.emplace_back( 103, 101, 100 );
    triangles.emplace_back( 92, 104, 103 );
    triangles.emplace_back( 104, 105, 103 );
    triangles.emplace_back( 103, 105, 101 );
    triangles.emplace_back( 105, 102, 101 );
    triangles.emplace_back( 91, 87, 104 );
    triangles.emplace_back( 87, 86, 104 );
    triangles.emplace_back( 104, 86, 105 );
    triangles.emplace_back( 86, 85, 105 );
    triangles.emplace_back( 105, 85, 102 );
    triangles.emplace_back( 85, 10, 102 );
    triangles.emplace_back( 100, 97, 12 );
    triangles.emplace_back( 101, 106, 100 );
    triangles.emplace_back( 102, 107, 101 );
    triangles.emplace_back( 100, 106, 97 );
    triangles.emplace_back( 106, 98, 97 );
    triangles.emplace_back( 101, 107, 106 );
    triangles.emplace_back( 107, 108, 106 );
    triangles.emplace_back( 106, 108, 98 );
    triangles.emplace_back( 108, 99, 98 );
    triangles.emplace_back( 102, 84, 107 );
    triangles.emplace_back( 84, 83, 107 );
    triangles.emplace_back( 107, 83, 108 );
    triangles.emplace_back( 83, 82, 108 );
    triangles.emplace_back( 108, 82, 99 );
    triangles.emplace_back( 82, 9, 99 );
    triangles.emplace_back( 97, 94, 12 );
    triangles.emplace_back( 98, 109, 97 );
    triangles.emplace_back( 99, 110, 98 );
    triangles.emplace_back( 97, 109, 94 );
    triangles.emplace_back( 109, 95, 94 );
    triangles.emplace_back( 98, 110, 109 );
    triangles.emplace_back( 110, 111, 109 );
    triangles.emplace_back( 109, 111, 95 );
    triangles.emplace_back( 111, 96, 95 );
    triangles.emplace_back( 99, 81, 110 );
    triangles.emplace_back( 81, 80, 110 );
    triangles.emplace_back( 110, 80, 111 );
    triangles.emplace_back( 80, 79, 111 );
    triangles.emplace_back( 111, 79, 96 );
    triangles.emplace_back( 79, 8, 96 );
    triangles.emplace_back( 94, 88, 12 );
    triangles.emplace_back( 95, 112, 94 );
    triangles.emplace_back( 96, 113, 95 );
    triangles.emplace_back( 94, 112, 88 );
    triangles.emplace_back( 112, 89, 88 );
    triangles.emplace_back( 95, 113, 112 );
    triangles.emplace_back( 113, 114, 112 );
    triangles.emplace_back( 112, 114, 89 );
    triangles.emplace_back( 114, 90, 89 );
    triangles.emplace_back( 96, 78, 113 );
    triangles.emplace_back( 78, 77, 113 );
    triangles.emplace_back( 113, 77, 114 );
    triangles.emplace_back( 77, 76, 114 );
    triangles.emplace_back( 114, 76, 90 );
    triangles.emplace_back( 76, 7, 90 );
    triangles.emplace_back( 88, 93, 12 );
    triangles.emplace_back( 89, 115, 88 );
    triangles.emplace_back( 90, 116, 89 );
    triangles.emplace_back( 88, 115, 93 );
    triangles.emplace_back( 115, 92, 93 );
    triangles.emplace_back( 89, 116, 115 );
    triangles.emplace_back( 116, 117, 115 );
    triangles.emplace_back( 115, 117, 92 );
    triangles.emplace_back( 117, 91, 92 );
    triangles.emplace_back( 90, 75, 116 );
    triangles.emplace_back( 75, 74, 116 );
    triangles.emplace_back( 116, 74, 117 );
    triangles.emplace_back( 74, 73, 117 );
    triangles.emplace_back( 117, 73, 91 );
    triangles.emplace_back( 73, 11, 91 );
    triangles.emplace_back( 48, 87, 11 );
    triangles.emplace_back( 47, 118, 48 );
    triangles.emplace_back( 46, 119, 47 );
    triangles.emplace_back( 48, 118, 87 );
    triangles.emplace_back( 118, 86, 87 );
    triangles.emplace_back( 47, 119, 118 );
    triangles.emplace_back( 119, 120, 118 );
    triangles.emplace_back( 118, 120, 86 );
    triangles.emplace_back( 120, 85, 86 );
    triangles.emplace_back( 46, 69, 119 );
    triangles.emplace_back( 69, 68, 119 );
    triangles.emplace_back( 119, 68, 120 );
    triangles.emplace_back( 68, 67, 120 );
    triangles.emplace_back( 120, 67, 85 );
    triangles.emplace_back( 67, 10, 85 );
    triangles.emplace_back( 72, 84, 10 );
    triangles.emplace_back( 71, 121, 72 );
    triangles.emplace_back( 70, 122, 71 );
    triangles.emplace_back( 72, 121, 84 );
    triangles.emplace_back( 121, 83, 84 );
    triangles.emplace_back( 71, 122, 121 );
    triangles.emplace_back( 122, 123, 121 );
    triangles.emplace_back( 121, 123, 83 );
    triangles.emplace_back( 123, 82, 83 );
    triangles.emplace_back( 70, 63, 122 );
    triangles.emplace_back( 63, 62, 122 );
    triangles.emplace_back( 122, 62, 123 );
    triangles.emplace_back( 62, 61, 123 );
    triangles.emplace_back( 123, 61, 82 );
    triangles.emplace_back( 61, 9, 82 );
    triangles.emplace_back( 66, 81, 9 );
    triangles.emplace_back( 65, 124, 66 );
    triangles.emplace_back( 64, 125, 65 );
    triangles.emplace_back( 66, 124, 81 );
    triangles.emplace_back( 124, 80, 81 );
    triangles.emplace_back( 65, 125, 124 );
    triangles.emplace_back( 125, 126, 124 );
    triangles.emplace_back( 124, 126, 80 );
    triangles.emplace_back( 126, 79, 80 );
    triangles.emplace_back( 64, 57, 125 );
    triangles.emplace_back( 57, 56, 125 );
    triangles.emplace_back( 125, 56, 126 );
    triangles.emplace_back( 56, 55, 126 );
    triangles.emplace_back( 126, 55, 79 );
    triangles.emplace_back( 55, 8, 79 );
    triangles.emplace_back( 60, 78, 8 );
    triangles.emplace_back( 59, 127, 60 );
    triangles.emplace_back( 58, 128, 59 );
    triangles.emplace_back( 60, 127, 78 );
    triangles.emplace_back( 127, 77, 78 );
    triangles.emplace_back( 59, 128, 127 );
    triangles.emplace_back( 128, 129, 127 );
    triangles.emplace_back( 127, 129, 77 );
    triangles.emplace_back( 129, 76, 77 );
    triangles.emplace_back( 58, 51, 128 );
    triangles.emplace_back( 51, 50, 128 );
    triangles.emplace_back( 128, 50, 129 );
    triangles.emplace_back( 50, 49, 129 );
    triangles.emplace_back( 129, 49, 76 );
    triangles.emplace_back( 49, 7, 76 );
    triangles.emplace_back( 54, 75, 7 );
    triangles.emplace_back( 53, 130, 54 );
    triangles.emplace_back( 52, 131, 53 );
    triangles.emplace_back( 54, 130, 75 );
    triangles.emplace_back( 130, 74, 75 );
    triangles.emplace_back( 53, 131, 130 );
    triangles.emplace_back( 131, 132, 130 );
    triangles.emplace_back( 130, 132, 74 );
    triangles.emplace_back( 132, 73, 74 );
    triangles.emplace_back( 52, 45, 131 );
    triangles.emplace_back( 45, 44, 131 );
    triangles.emplace_back( 131, 44, 132 );
    triangles.emplace_back( 44, 43, 132 );
    triangles.emplace_back( 132, 43, 73 );
    triangles.emplace_back( 43, 11, 73 );
    triangles.emplace_back( 67, 72, 10 );
    triangles.emplace_back( 68, 133, 67 );
    triangles.emplace_back( 69, 134, 68 );
    triangles.emplace_back( 67, 133, 72 );
    triangles.emplace_back( 133, 71, 72 );
    triangles.emplace_back( 68, 134, 133 );
    triangles.emplace_back( 134, 135, 133 );
    triangles.emplace_back( 133, 135, 71 );
    triangles.emplace_back( 135, 70, 71 );
    triangles.emplace_back( 69, 42, 134 );
    triangles.emplace_back( 42, 41, 134 );
    triangles.emplace_back( 134, 41, 135 );
    triangles.emplace_back( 41, 40, 135 );
    triangles.emplace_back( 135, 40, 70 );
    triangles.emplace_back( 40, 5, 70 );
    triangles.emplace_back( 61, 66, 9 );
    triangles.emplace_back( 62, 136, 61 );
    triangles.emplace_back( 63, 137, 62 );
    triangles.emplace_back( 61, 136, 66 );
    triangles.emplace_back( 136, 65, 66 );
    triangles.emplace_back( 62, 137, 136 );
    triangles.emplace_back( 137, 138, 136 );
    triangles.emplace_back( 136, 138, 65 );
    triangles.emplace_back( 138, 64, 65 );
    triangles.emplace_back( 63, 39, 137 );
    triangles.emplace_back( 39, 38, 137 );
    triangles.emplace_back( 137, 38, 138 );
    triangles.emplace_back( 38, 37, 138 );
    triangles.emplace_back( 138, 37, 64 );
    triangles.emplace_back( 37, 4, 64 );
    triangles.emplace_back( 55, 60, 8 );
    triangles.emplace_back( 56, 139, 55 );
    triangles.emplace_back( 57, 140, 56 );
    triangles.emplace_back( 55, 139, 60 );
    triangles.emplace_back( 139, 59, 60 );
    triangles.emplace_back( 56, 140, 139 );
    triangles.emplace_back( 140, 141, 139 );
    triangles.emplace_back( 139, 141, 59 );
    triangles.emplace_back( 141, 58, 59 );
    triangles.emplace_back( 57, 33, 140 );
    triangles.emplace_back( 33, 32, 140 );
    triangles.emplace_back( 140, 32, 141 );
    triangles.emplace_back( 32, 31, 141 );
    triangles.emplace_back( 141, 31, 58 );
    triangles.emplace_back( 31, 3, 58 );
    triangles.emplace_back( 49, 54, 7 );
    triangles.emplace_back( 50, 142, 49 );
    triangles.emplace_back( 51, 143, 50 );
    triangles.emplace_back( 49, 142, 54 );
    triangles.emplace_back( 142, 53, 54 );
    triangles.emplace_back( 50, 143, 142 );
    triangles.emplace_back( 143, 144, 142 );
    triangles.emplace_back( 142, 144, 53 );
    triangles.emplace_back( 144, 52, 53 );
    triangles.emplace_back( 51, 21, 143 );
    triangles.emplace_back( 21, 20, 143 );
    triangles.emplace_back( 143, 20, 144 );
    triangles.emplace_back( 20, 19, 144 );
    triangles.emplace_back( 144, 19, 52 );
    triangles.emplace_back( 19, 2, 52 );
    triangles.emplace_back( 43, 48, 11 );
    triangles.emplace_back( 44, 145, 43 );
    triangles.emplace_back( 45, 146, 44 );
    triangles.emplace_back( 43, 145, 48 );
    triangles.emplace_back( 145, 47, 48 );
    triangles.emplace_back( 44, 146, 145 );
    triangles.emplace_back( 146, 147, 145 );
    triangles.emplace_back( 145, 147, 47 );
    triangles.emplace_back( 147, 46, 47 );
    triangles.emplace_back( 45, 24, 146 );
    triangles.emplace_back( 24, 23, 146 );
    triangles.emplace_back( 146, 23, 147 );
    triangles.emplace_back( 23, 22, 147 );
    triangles.emplace_back( 147, 22, 46 );
    triangles.emplace_back( 22, 6, 46 );
    triangles.emplace_back( 27, 42, 6 );
    triangles.emplace_back( 26, 148, 27 );
    triangles.emplace_back( 25, 149, 26 );
    triangles.emplace_back( 27, 148, 42 );
    triangles.emplace_back( 148, 41, 42 );
    triangles.emplace_back( 26, 149, 148 );
    triangles.emplace_back( 149, 150, 148 );
    triangles.emplace_back( 148, 150, 41 );
    triangles.emplace_back( 150, 40, 41 );
    triangles.emplace_back( 25, 36, 149 );
    triangles.emplace_back( 36, 35, 149 );
    triangles.emplace_back( 149, 35, 150 );
    triangles.emplace_back( 35, 34, 150 );
    triangles.emplace_back( 150, 34, 40 );
    triangles.emplace_back( 34, 5, 40 );
    triangles.emplace_back( 34, 39, 5 );
    triangles.emplace_back( 35, 151, 34 );
    triangles.emplace_back( 36, 152, 35 );
    triangles.emplace_back( 34, 151, 39 );
    triangles.emplace_back( 151, 38, 39 );
    triangles.emplace_back( 35, 152, 151 );
    triangles.emplace_back( 152, 153, 151 );
    triangles.emplace_back( 151, 153, 38 );
    triangles.emplace_back( 153, 37, 38 );
    triangles.emplace_back( 36, 30, 152 );
    triangles.emplace_back( 30, 29, 152 );
    triangles.emplace_back( 152, 29, 153 );
    triangles.emplace_back( 29, 28, 153 );
    triangles.emplace_back( 153, 28, 37 );
    triangles.emplace_back( 28, 4, 37 );
    triangles.emplace_back( 28, 33, 4 );
    triangles.emplace_back( 29, 154, 28 );
    triangles.emplace_back( 30, 155, 29 );
    triangles.emplace_back( 28, 154, 33 );
    triangles.emplace_back( 154, 32, 33 );
    triangles.emplace_back( 29, 155, 154 );
    triangles.emplace_back( 155, 156, 154 );
    triangles.emplace_back( 154, 156, 32 );
    triangles.emplace_back( 156, 31, 32 );
    triangles.emplace_back( 30, 15, 155 );
    triangles.emplace_back( 15, 14, 155 );
    triangles.emplace_back( 155, 14, 156 );
    triangles.emplace_back( 14, 13, 156 );
    triangles.emplace_back( 156, 13, 31 );
    triangles.emplace_back( 13, 3, 31 );
    triangles.emplace_back( 22, 27, 6 );
    triangles.emplace_back( 23, 157, 22 );
    triangles.emplace_back( 24, 158, 23 );
    triangles.emplace_back( 22, 157, 27 );
    triangles.emplace_back( 157, 26, 27 );
    triangles.emplace_back( 23, 158, 157 );
    triangles.emplace_back( 158, 159, 157 );
    triangles.emplace_back( 157, 159, 26 );
    triangles.emplace_back( 159, 25, 26 );
    triangles.emplace_back( 24, 18, 158 );
    triangles.emplace_back( 18, 17, 158 );
    triangles.emplace_back( 158, 17, 159 );
    triangles.emplace_back( 17, 16, 159 );
    triangles.emplace_back( 159, 16, 25 );
    triangles.emplace_back( 16, 1, 25 );
    triangles.emplace_back( 13, 21, 3 );
    triangles.emplace_back( 14, 160, 13 );
    triangles.emplace_back( 15, 161, 14 );
    triangles.emplace_back( 13, 160, 21 );
    triangles.emplace_back( 160, 20, 21 );
    triangles.emplace_back( 14, 161, 160 );
    triangles.emplace_back( 161, 162, 160 );
    triangles.emplace_back( 160, 162, 20 );
    triangles.emplace_back( 162, 19, 20 );
    triangles.emplace_back( 15, 16, 161 );
    triangles.emplace_back( 16, 17, 161 );
    triangles.emplace_back( 161, 17, 162 );
    triangles.emplace_back( 17, 18, 162 );
    triangles.emplace_back( 162, 18, 19 );
    triangles.emplace_back( 18, 2, 19 );

    for (Vector& i : triangles)
        i = i + Vector(-1, -1, -1);

    return new Mesh(vertices, colours, triangles, normals);
}

Mesh* Mesh::monkey() {
    
}