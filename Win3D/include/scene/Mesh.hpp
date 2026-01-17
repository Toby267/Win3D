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
    const std::vector<Vector> VERTICES_ORIGINAL;
    const std::vector<Colour> COLOURS_ORIGINAL;
    const std::vector<Vector> TRIANGLES_ORIGINAL;
    const std::vector<Vector> NORMALS_ORIGINAL;

    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> triangles;
    std::vector<Vector> normals;

    Matrix scale       = Matrix::scale(100, 100, 100);
    Matrix translation = Matrix::translate(0, 0, 0);
    Matrix rotation    = Matrix::rotation(0, 0, 0);

    Matrix affineTransform = translation * scale * rotation;

    Mat::Material material = Mat::DisneyDiffuse{0.5, 0.5};

public:
    //constructors/destructor
    Mesh(std::vector<Vector> vertices, std::vector<Colour> colours, std::vector<Vector> triangles);
    Mesh(std::vector<Vector> vertices, std::vector<Colour> colours, std::vector<Vector> triangles, std::vector<Vector> normals);

    //getters/setters
    std::vector<Vector>& getVertices();
    std::vector<Colour>& getColours();
    std::vector<Vector>& getTriangles();

    void setScale(Matrix scale);
    void setTranslation(Matrix translation);
    void setRotation(Matrix rotation);
    void setMaterial(Mat::Material material);

    //general public methods
    void toWorldSpace();
    void applyAffineTransform(Matrix matrix);
    void applyTransform(Matrix matrix);

    void reset();
    void clip();
    Aabb calcBBox() const;
    bool hit(const Ray& ray, TrianglePoint& triangle, float& t) const;

    //operator overloads
    friend std::ostream& operator<<(std::ostream& os, const Mesh& matrix);

    //static methods
    static Mesh* cube();
    static Mesh* sphere();
    static Mesh* monkey();
    static Mesh* triangle();

private:
    //private methods
    bool mollerTrumboreIntersection(const Ray& ray, const Vector& triangle, float& u, float& v, float &t) const;
};