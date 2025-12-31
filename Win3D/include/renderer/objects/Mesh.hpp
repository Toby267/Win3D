#pragma once

#include <vector>

#include "Object.hpp"
#include "util/Matrix.hpp"
#include "util/Vector.hpp"
#include "util/Colour.hpp"

/**
 * stores the data of an object. the vertices is just a list of vectors, one per vertex. colours[i] is the colour of vertices[i].
 * triangles[i] stores the first tirangle, where triangle[i][0] is v1, triangle[i][1] is v2, and triangle[i][2] is v3.
 * we'll get to uv maps later
 */
class Mesh : public Object{
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

    //public methods
    void transform();
    void applyAffineTransformation(const Matrix& m);
    void applyTransformation(const Matrix& m);
    void normalise();

    void clip();

    bool hit(Ray& ray) override;

    //operator overloads
    friend std::ostream& operator<<(std::ostream& os, const Mesh& m);

    //static methods
    static Mesh cube(Colour c);
    static Mesh icoSphereSmall(Colour c);
    static Mesh icoSphere(Colour c);
};