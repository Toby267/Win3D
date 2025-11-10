#include "scene/Object3D.hpp"

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
void Object3D::applyTransformation(Matrix m) {
    for (Vector& vertex : vertices) {
        vertex = m * vertex;
        vertex = vertex / vertex.w();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ STATIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object3D Object3D::cube() {
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
    colours.emplace_back(Colour::green());
    colours.emplace_back(Colour::green());
    colours.emplace_back(Colour::green());
    colours.emplace_back(Colour::green());
    colours.emplace_back(Colour::green());
    colours.emplace_back(Colour::green());
    colours.emplace_back(Colour::blue());

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
