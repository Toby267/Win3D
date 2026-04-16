#include "scene/objects/Mesh.hpp"
#include "renderer/Ray.hpp"
#include "scene/dataStructures/BvhNode.hpp"
#include "scene/objects/Materials.hpp"
#include "scene/core/SceneUtil.hpp"
#include "util/Util.hpp"

#include <cassert>
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// default constructor taking in the index buffer and vertex buffer
Mesh::Mesh(IndexBuffer ib, VertexBuffer vb)
    : INDEX_BUFFER(ib), VERTEX_BUFFER(vb), indexBuffer(ib), vertexBuffer(vb)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// returns all the data of the mesh in a std::vector<Triangle> form
std::vector<Triangle> Mesh::getTriangles() const {
    std::vector<Triangle> triangles;
    triangles.reserve(indexBuffer.size());

    for (int i = 2; i < indexBuffer.size(); i += 3) {
        Index i1 = indexBuffer[i-2];
        Index i2 = indexBuffer[i-1];
        Index i3 = indexBuffer[i];

        Vertex v1, v2, v3;
        
        v1.position = vertexBuffer[i1.position].position,
        v1.colour   = vertexBuffer[i1.colour].colour,
        v1.normal   = vertexBuffer[i1.normal].normal,
        v1.u        = vertexBuffer[i1.uv].u,
        v1.v        = vertexBuffer[i1.uv].v,

        v2.position = vertexBuffer[i2.position].position,
        v2.colour   = vertexBuffer[i2.colour].colour,
        v2.normal   = vertexBuffer[i2.normal].normal,
        v2.u        = vertexBuffer[i2.uv].u,
        v2.v        = vertexBuffer[i2.uv].v,

        v3.position = vertexBuffer[i3.position].position,
        v3.colour   = vertexBuffer[i3.colour].colour,
        v3.normal   = vertexBuffer[i3.normal].normal,
        v3.u        = vertexBuffer[i3.uv].u,
        v3.v        = vertexBuffer[i3.uv].v,
        
        triangles.emplace_back(v1, v2, v3);
    }

    return triangles;
}

// transformation setters
void Mesh::setScale(Matrix s) {
    scale = s;
    affineTransform = translation * rotation * scale;
}
void Mesh::setTranslation(Matrix t) {
    translation = t;
    affineTransform = translation * rotation * scale;
}
void Mesh::setRotation(Matrix r) {
    rotation = r;
    affineTransform = translation * rotation * scale;
}
void Mesh::setMaterial(Mat::Material m) {
    material = m;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// transformation functions
void Mesh::toWorldSpace() {
    for (Vertex& vertex : vertexBuffer) {
        vertex.position = affineTransform * vertex.position;
    }
}
void Mesh::applyAffineTransform(Matrix m) {
    for (Vertex& vertex : vertexBuffer) {
        vertex.position = m * vertex.position;
    }
}
void Mesh::applyTransform(Matrix m) {
    for (Vertex& vertex : vertexBuffer) {
        vertex.position = m * vertex.position;
        vertex.position = vertex.position / vertex.position.w();
    }
}
void Mesh::transformNormals(Matrix m) {
    m = m * rotation;
    Matrix r = Matrix::asMat3(m);
    
    for (Vertex& vertex : vertexBuffer) {
        vertex.normal = r * vertex.normal;
    }
}

// reset all data to how it was at creation time
void Mesh::reset() {
    vertexBuffer = VERTEX_BUFFER;
    indexBuffer = INDEX_BUFFER;
    delete tree;
    tree = nullptr;
}

// perform canonical view volume clipping
void Mesh::clip() {
    double xMax = vertexBuffer[0].position.x(), yMax = vertexBuffer[0].position.y(), zMax = vertexBuffer[0].position.z();
    double xMin = vertexBuffer[0].position.x(), yMin = vertexBuffer[0].position.y(), zMin = vertexBuffer[0].position.z();

    for (Vertex& vertex : vertexBuffer) {
        if (vertex.position.x() > xMax) xMax = vertex.position.x();
        if (vertex.position.y() > yMax) yMax = vertex.position.y();
        if (vertex.position.z() > zMax) zMax = vertex.position.z();

        if (vertex.position.x() < xMin) xMin = vertex.position.x();
        if (vertex.position.y() < yMin) yMin = vertex.position.y();
        if (vertex.position.z() < zMin) zMin = vertex.position.z();
    }

    if (xMin >  1 || yMin >  1 || zMin >  1) indexBuffer.clear();
    if (xMax < -1 || yMax < -1 || zMax < -1) indexBuffer.clear();
}

// ray tracing functions
void Mesh::createAccelDataStrucutre() {
    std::vector<Triangle> triangles = getTriangles();
    tree = new BvhTree(triangles);
}
HitRecord Mesh::intersect(const Ray& ray) const {
    HitRecord rec = tree->intersect(ray);
    rec.mat = material;
    return rec;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * --------------------------------------- [ OPERATOR OVERLOADS ] -------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, const Mesh& obj) {
    for (const Vertex& v : obj.vertexBuffer)
        os << "v " << v.position << '\n';
    for (const Vertex& v : obj.vertexBuffer)
        os << "vn " << v.normal << '\n';
    for (const Vertex& v : obj.vertexBuffer) {
        os << "vt " << v.u << ' ';
        os << v.v << '\n';
    }

    int ii = 0;
    for (const Index& i : obj.indexBuffer) {
        os << "f ";
        os << i.position+1 << '/';
        os << i.uv+1 << '/';
        os << i.normal+1 << ' ';

        ii++;
        if (ii == 3) {
            os << '\n';
            ii = 0;
        }
    }

    for (const Vertex& v : obj.vertexBuffer)
        os << v.colour << '\n';

    return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ STATIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// returns a mesh consisting of a single triangle
Mesh* Mesh::triangle() {
    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> normals;
    std::vector<double> us, vs;

    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;

    vertices.emplace_back( -1.000000, 0.000000, 1.000000, 1 );
    vertices.emplace_back( 0.000000, 1.000000, 1.000000, 1 );
    vertices.emplace_back( 1.000000, 0.000000, 1.000000, 1 );

    colours.emplace_back(Colour::red());
    colours.emplace_back(Colour::green());
    colours.emplace_back(Colour::blue());
    
    normals.emplace_back( 0.0, 0.0, -0.1 );
    normals.emplace_back( 0.0, 0.0, -0.1 );
    normals.emplace_back( 0.0, 0.0, -0.1 );

    us.emplace_back(0.0); vs.emplace_back(0.0);
    us.emplace_back(0.0); vs.emplace_back(0.0);
    us.emplace_back(0.0); vs.emplace_back(0.0);

    indexBuffer.emplace_back(Index{0, 0, 0, 0}); indexBuffer.emplace_back(Index{1, 1, 1, 1}); indexBuffer.emplace_back(Index{2, 2, 2, 2});//done

    for (int i = 0; i < normals.size(); i++)
        vertexBuffer.emplace_back(vertices[i], colours[i], normals[i], us[i], vs[i]);
    
    return new Mesh(indexBuffer, vertexBuffer);
}
