#pragma once

#include <vector>

#include "renderer/Ray.hpp"
#include "scene/aabb.hpp"
#include "util/Matrix.hpp"
#include "util/Vector.hpp"
#include "util/Colour.hpp"

/**
 * stores the data of an object. the vertices is just a list of vectors, one per vertex. colours[i] is the colour of vertices[i].
 * triangles[i] stores the first tirangle, where triangle[i][0] is v1, triangle[i][1] is v2, and triangle[i][2] is v3.
 * we'll get to uv maps later
 */
class Mesh {
private:
    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> triangles;
    std::vector<Vector> uvCoordinates;

    Matrix scale       = Matrix::scale(1, 1, 1);
    Matrix translation = Matrix::translate(0, 0, 0);
    Matrix rotation    = Matrix::rotation(0, 0, 0);

    Matrix affineTransform = translation * scale * rotation;

public:
    //constructors/destructor
    Mesh(std::vector<Vector> vertices, std::vector<Colour> colours, std::vector<Vector> triangles);

    //getters/setters
    std::vector<Vector>& getVertices();
    std::vector<Colour>& getColours();
    std::vector<Vector>& getTriangles();

    void setScale(Matrix s);
    void setTranslation(Matrix t);
    void setRotation(Matrix r);

    //general public methods
    void toWorldSpace();
    void applyAffineTransform(Matrix m);
    void applyTransform(Matrix m);

    void clip();

    aabb calcBBox();
    bool hit(Ray& ray);

    //operator overloads
    friend std::ostream& operator<<(std::ostream& os, const Mesh& m);

    //static methods
    static Mesh* cube(Colour c);
    static Mesh* icoSphereSmall(Colour c);
    static Mesh* icoSphere(Colour c);

private:
    //private methods
    float mollerTrumboreIntersection(Ray ray, Vector triangle);
};