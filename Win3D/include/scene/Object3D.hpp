#pragma once

#include <vector>

#include "renderer/Bitmap3D.hpp"

#include "util/Matrix.hpp"
#include "util/Vector.hpp"
#include "util/Colour.hpp"

/**
 * stores the data of an object. the vertices is just a list of vectors, one per vertex. colours[i] is the colour of vertices[i].
 * triangles[i] stores the first tirangle, where triangle[i][0] is v1, triangle[i][1] is v2, and triangle[i][2] is v3.
 * we'll get to uv maps later
 */
class Object3D {
private:
    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> triangles;
    std::vector<Vector> uvCoordinates;
   

    Matrix scale       = Matrix(4, 4);
    Matrix translation = Matrix(4, 4);

public:
    Object3D();
    Object3D(std::vector<Vector> vertices, std::vector<Colour> colours, std::vector<Vector> triangles);
    Object3D(std::vector<Vector> vertices, std::vector<Colour> colours, std::vector<Vector> triangles, Matrix scale, Matrix translation);

    static Object3D cube(Matrix scale, Matrix translation);

    void draw(Bitmap3D bmap);
};