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
void Object3D::setCamera(Camera* camera) {
    cameraRef = camera;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Object3D::transform() {
    for (Vector& vertex : vertices) {
        vertex = affineTransform * vertex;
    }
    std::cout << "\n\nvertex 0: " << vertices[0] << '\n';
}
void Object3D::project() {
    for (Vector& vertex : vertices) {
        vertex = cameraRef->getProjection() * vertex;
        vertex = vertex / vertex.w();
    }

    std::cout << "vertex 0: " << vertices[0] <<"\n";
}
void Object3D::applyViewportTransformation(Matrix transformationMatrix) {
    for (Vector& vertex : vertices) {
        vertex = transformationMatrix * vertex;
    }
    std::cout << "vertex 0: " << vertices[0] <<"\n\n";
}
void Object3D::draw(Bitmap3D& bmap) {
    for (Vector t : triangles) {
        bmap.drawTriangle(vertices[t[0]], vertices[t[1]], vertices[t[2]], colours[t[0]], colours[t[1]], colours[t[2]]);
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
