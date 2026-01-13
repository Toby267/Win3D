#pragma once

#include "renderer/Ray.hpp"
#include "scene/Aabb.hpp"
#include "scene/Materials.hpp"
#include "util/Matrix.hpp"
#include "util/Vector.hpp"
#include "util/Colour.hpp"

#include <vector>

/**
 * stores the data of an object. the vertices is just a list of vectors, one per vertex. colours[i] is the colour of vertices[i].
 * triangles[i] stores the first tirangle, where triangle[i][0] is v1, triangle[i][1] is v2, and triangle[i][2] is v3.
 * we'll get to uv maps later
 */
class Mesh {
private:
    const std::vector<Vector> vertices_original;
    const std::vector<Colour> colours_original;
    const std::vector<Vector> triangles_original;

    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> triangles;

    Matrix scale       = Matrix::scale(100, 100, 100);
    Matrix translation = Matrix::translate(0, 0, 0);
    Matrix rotation    = Matrix::rotation(0, 0, 0);

    Matrix affineTransform = translation * scale * rotation;

    Materials::Shader material = Materials::DisneyDiffuse{Colour::blue(), 0.5, 0.5};

public:
    //constructors/destructor
    Mesh(std::vector<Vector> vertices, std::vector<Colour> colours, std::vector<Vector> triangles);

    //getters/setters
    std::vector<Vector>& getVertices();
    std::vector<Colour>& getColours();
    std::vector<Vector>& getTriangles();

    void setScale(Matrix scale);
    void setTranslation(Matrix translation);
    void setRotation(Matrix rotation);

    //general public methods
    void toWorldSpace();
    void applyAffineTransform(Matrix matrix);
    void applyTransform(Matrix matrix);

    void reset();
    void clip();
    Aabb calcBBox() const;
    bool hit(Ray& ray) const;

    //operator overloads
    friend std::ostream& operator<<(std::ostream& os, const Mesh& matrix);

    //static methods
    static Mesh* cube(Colour colour);
    static Mesh* icoSphereSmall(Colour colour);
    static Mesh* icoSphere(Colour colour);

private:
    //private methods
    float mollerTrumboreIntersection(Ray& ray, const Vector& triangle) const;
};