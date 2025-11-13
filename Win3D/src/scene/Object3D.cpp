#include "scene/Object3D.hpp"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Default constructor that sets up the object based on the given vertices, colours, and triangles
 * 
 * @param vertices  the vertices of the object
 * @param colours   the colour of each vertex
 * @param triangles the indeces of the vertices array, determining the traingles of the object
 */
Object3D::Object3D(std::vector<Vector> vertices, std::vector<Colour> colours, std::vector<Vector> triangles)
    : vertices(vertices), colours(colours), triangles(triangles)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//returns the vertices of the object
std::vector<Vector>& Object3D::getVertices() {
    return vertices;
}
//returns the colours of the object
std::vector<Colour>& Object3D::getColours() {
    return colours;
}
//returns the triangles of the object
std::vector<Vector>& Object3D::getTriangles() {
    return triangles;
}

//sets the scale of the object
void Object3D::setScale(Matrix s) {
    scale = s;
    affineTransform = translation * rotation * scale;
}
//sets the translation of the object
void Object3D::setTranslation(Matrix t) {
    translation = t;
    affineTransform = translation * rotation * scale;
}
//sets the rotation of the object
void Object3D::setRotation(Matrix r) {
    rotation = r;
    affineTransform = translation * rotation * scale;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//transforms the object into world space
void Object3D::transform() {
    for (Vector& vertex : vertices) {
        vertex = affineTransform * vertex;
    }
}
//applys an affine transformation to the object
void Object3D::applyAffineTransformation(const Matrix& m) {
    for (Vector& vertex : vertices) {
        vertex = m * vertex;
        
    }
}
//applys a non-affine transformation to the object, and normalises it
void Object3D::applyTransformation(const Matrix& m) {
    for (Vector& vertex : vertices) {
        vertex = m * vertex;
        vertex = vertex / vertex.w();
    }
}


//clips the object if it is outside the canonical view volume
//TODO: this should be done in the geometry processing class, and you should fix the fact that it renders in front and behind, then clips behind.
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * --------------------------------------- [ OPERATOR OVERLOADS ] -------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//prints out the object
std::ostream& operator<<(std::ostream& os, const Object3D& obj) {
    os << "printing out object vertices:\n";
    for (const Vector& vertex : obj.vertices) {
        os << "vertex: " << vertex << '\n';
    }
    return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ STATIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//sets up, and returns a cube
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
