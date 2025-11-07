#include "scene/Object3D.hpp"

Object3D::Object3D() {};

Object3D::Object3D(std::vector<Vector> vertices, std::vector<Colour> colours, std::vector<Vector> triangles)
    : vertices(vertices), colours(colours), triangles(triangles) { }

Object3D::Object3D(std::vector<Vector> vertices, std::vector<Colour> colours, std::vector<Vector> triangles, Matrix scale, Matrix translation)
    : vertices(vertices), colours(colours), triangles(triangles), scale(scale), translation(translation) { }

Object3D Object3D::cube(Matrix scale, Matrix translation)
{
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
    colours.emplace_back(Colour::red());
    colours.emplace_back(Colour::red());
    colours.emplace_back(Colour::red());
    colours.emplace_back(Colour::red());
    colours.emplace_back(Colour::red());
    colours.emplace_back(Colour::red());
    colours.emplace_back(Colour::red());

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

    return Object3D(vertices, colours, triangles, scale, translation);
}