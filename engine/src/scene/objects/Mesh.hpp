#pragma once

#include "renderer/Ray.hpp"
#include "scene/dataStructures/Aabb.hpp"
#include "scene/core/SceneUtil.hpp"
#include "scene/dataStructures/BvhNode.hpp"
#include "scene/objects/Materials.hpp"
#include "util/Util.hpp"
#include "scene/core/SceneUtil.hpp"

/**
 * Stores the data of an object, including the vertex buffer, index buffer, bounding volume hierarchy, transformation data, and material
 * 
 * has funcitonality for transformations, intersection, and clipping
 */
class Mesh {
private:
    // original copies of buffers
    const VertexBuffer VERTEX_BUFFER;
    const IndexBuffer INDEX_BUFFER;

    // buffers that are modified during rendering
    IndexBuffer indexBuffer;
    VertexBuffer vertexBuffer;

    // acceleration data structures
    BvhTree* tree = nullptr;

    // transformations
    Matrix scale       = Matrix::scale(100, 100, 100);
    Matrix translation = Matrix::translate(0, 0, 0);
    Matrix rotation    = Matrix::rotation(0, 0, 0);

    Matrix affineTransform = translation * scale * rotation;

    // material
    Mat::Material material = Mat::DisneyBSDF{
        0.4,    // roughness
        0.0,    // subsurface
        0.2,    // sheen
        0.9,    // sheenTint
        0.6,    // anisotropic
        0.7,    // metallic
        1.0,    // specular
        0.2,    // specularTint
        1.0,    // clearcoat
        1.0,    // clearcoatGloss
    };

public:
    // constructors/destructor
    Mesh(IndexBuffer indexBuffer, VertexBuffer vertexBuffer);

    // getters/setters
    std::vector<Triangle> getTriangles() const;

    void setScale(Matrix scale);
    void setTranslation(Matrix translation);
    void setRotation(Matrix rotation);
    void setMaterial(Mat::Material material);

    // general public methods
    void toWorldSpace();
    void applyAffineTransform(Matrix matrix);
    void applyTransform(Matrix matrix);
    void transformNormals(Matrix matrix);
    void reset();

    // ray tracing methods
    void createAccelDataStrucutre();
    HitRecord intersect(const Ray& ray) const;

    // raster methods
    void clip();

    // operator overloads
    friend std::ostream& operator<<(std::ostream& os, const Mesh& matrix);

    // static methods
    static Mesh* triangle();
};
