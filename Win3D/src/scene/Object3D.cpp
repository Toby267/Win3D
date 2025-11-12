#include "scene/Object3D.hpp"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object3D::Object3D(std::vector<Vector> vertices, std::vector<Colour> colours, std::vector<Vector> triangles)
    : vertices(vertices), colours(colours), triangles(triangles)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::vector<Vector>& Object3D::getVertices() const {
    return vertices;
}
const std::vector<Colour>& Object3D::getColours() const {
    return colours;
}
const std::vector<Vector>& Object3D::getTriangles() const {
    return triangles;
}
const std::vector<Vector>& Object3D::getUvCoordinates() const {
    return uvCoordinates;
}

void Object3D::setScale(Matrix s) {
    scale = s;
    affineTransform = translation * rotation * scale;
}
void Object3D::setTranslation(Matrix t) {
    translation = t;
    affineTransform = translation * rotation * scale;
}
void Object3D::setRotation(Matrix r) {
    rotation = r;
    affineTransform = translation * rotation * scale;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Object3D::transform() {
    for (Vector& vertex : vertices) {
        vertex = affineTransform * vertex;
    }
}
void Object3D::applyTransformation(const Matrix& m) {
    for (Vector& vertex : vertices) {
        vertex = m * vertex;
        vertex = vertex / vertex.w();
    }
}

void Object3D::normalise() {
    for (Vector& vertex : vertices) {
        vertex = vertex / vertex.w();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ STATIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object3D Object3D::cube(Colour c) {
    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> triangles;

    vertices.emplace_back(-1, -1, -1, 1);
    vertices.emplace_back(-1, -1,  1, 1);
    vertices.emplace_back(-1,  1, -1, 1);
    vertices.emplace_back(-1,  1,  1, 1);
    vertices.emplace_back( 1, -1, -1, 1);
    vertices.emplace_back( 1, -1,  1, 1);
    vertices.emplace_back( 1,  1, -1, 1);
    vertices.emplace_back( 1,  1,  1, 1);

    colours.emplace_back(Colour::red());
    colours.emplace_back(c);
    colours.emplace_back(c);
    colours.emplace_back(c);
    colours.emplace_back(c);
    colours.emplace_back(c);
    colours.emplace_back(c);
    colours.emplace_back(Colour::green());

    triangles.emplace_back(0, 1, 2);
    triangles.emplace_back(1, 3, 2);
    triangles.emplace_back(4, 5, 6);
    triangles.emplace_back(5, 6, 7);
    triangles.emplace_back(0, 2, 4);
    triangles.emplace_back(2, 6, 4);
    triangles.emplace_back(1, 5, 3);
    triangles.emplace_back(5, 7, 3);
    triangles.emplace_back(2, 3, 6);
    triangles.emplace_back(3, 7, 6);
    triangles.emplace_back(0, 4, 1);
    triangles.emplace_back(1, 4, 5);

    return Object3D(vertices, colours, triangles);
}

void Object3D::clip() {
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

    if (xMin >  1 || yMin >  1 || zMin > 1) triangles.clear();
    if (xMax < -1 || yMax < -1 || zMax < 0) triangles.clear();
}


std::ostream& operator<<(std::ostream& os, const Object3D& obj) {
    os << "printing out object vertices:\n";
    for (const Vector& vertex : obj.vertices) {
        os << "vertex: " << vertex << '\n';
    }
    return os;
}