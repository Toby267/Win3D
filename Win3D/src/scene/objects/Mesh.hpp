#pragma once

#include "renderer/Ray.hpp"
#include "scene/dataStructures/Aabb.hpp"
#include "scene/dataStructures/BvhNode.hpp"
#include "scene/objects/Materials.hpp"
#include "util/Util.hpp"
#include "scene/core/SceneUtil.hpp"

/**
 * stores the data of an object. the vertices is just a list of vectors, one per vertex. colours[i] is the colour of vertices[i].
 * triangles[i] stores the first tirangle, where triangle[i][0] is v1, triangle[i][1] is v2, and triangle[i][2] is v3.
 * we'll get to uv maps later
 */
class Mesh {
private:
    const VertexBuffer VERTEX_BUFFER;

    IndexBuffer indexBuffer;
    VertexBuffer vertexBuffer;

    BvhTree* tree = nullptr;

    Matrix scale       = Matrix::scale(100, 100, 100);
    Matrix translation = Matrix::translate(0, 0, 0);
    Matrix rotation    = Matrix::rotation(0, 0, 0);

    Matrix affineTransform = translation * scale * rotation;

    Mat::Material material = Mat::DisneyDiffuse{0.5, 0.5};

public:
    //constructors/destructor
    Mesh(IndexBuffer indexBuffer, VertexBuffer vertexBuffer);

    //getters/setters
    std::vector<Triangle> getTriangles() const;

    void setScale(Matrix scale);
    void setTranslation(Matrix translation);
    void setRotation(Matrix rotation);
    void setMaterial(Mat::Material material);

    //general public methods
    void toWorldSpace();
    void applyAffineTransform(Matrix matrix);
    void applyTransform(Matrix matrix);
    void reset();

    //ray tracing stuff
    void updateAccelDataStrucutre();
    HitRecord intersect(const Ray& ray) const;

    //raster stuff
    void clip();

    //operator overloads
    friend std::ostream& operator<<(std::ostream& os, const Mesh& matrix);

    //static methods
    static Mesh* cube();
    static Mesh* sphere();
    static Mesh* triangle();
};
