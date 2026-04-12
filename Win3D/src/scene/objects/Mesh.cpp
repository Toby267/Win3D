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

Mesh::Mesh(IndexBuffer ib, VertexBuffer vb)
    : INDEX_BUFFER(ib), VERTEX_BUFFER(vb), indexBuffer(ib), vertexBuffer(vb)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #define PRINT

std::vector<Triangle> Mesh::getTriangles() const {
    std::vector<Triangle> triangles;
    triangles.reserve(indexBuffer.size());

    #ifdef PRINT

    for (const Vertex& v : vertexBuffer)
        std::cout << "v " << v.position << '\n';
    for (const Vertex& v : vertexBuffer)
        std::cout << "vn " << v.normal << '\n';
    for (const Vertex& v : vertexBuffer) {
        std::cout << "vt " << v.u << ' ';
        std::cout << v.v << '\n';
    }

    int ii = 0;
    for (const Index& i : indexBuffer) {
        std::cout << i.position+1 << '/';
        std::cout << i.uv+1 << '/';
        std::cout << i.normal+1 << ' ';

        ii++;
        if (ii == 3) {
            std::cout << '\n';
            ii = 0;
        }
    }

    for (const Vertex& v : vertexBuffer)
        std::cout << v.colour << '\n';

    std::cin.get();

    #endif

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

void Mesh::reset() {
    vertexBuffer = VERTEX_BUFFER;
    indexBuffer = INDEX_BUFFER;
    delete tree;
    tree = nullptr;
}

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
    os << "printing out object vertices:\n";
    for (const Vertex& vertex : obj.vertexBuffer) {
        os << "vertex: " << vertex.position << '\n';
    }
    return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ STATIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mesh* Mesh::cube() {
    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> normals;
    std::vector<double> us, vs;

    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;

    vertices.emplace_back( 1.000000, 1.000000, -1.000000, 1 );
    vertices.emplace_back( 1.000000, -1.000000, -1.000000, 1 );
    vertices.emplace_back( 1.000000, 1.000000, 1.000000, 1 );
    vertices.emplace_back( 1.000000, -1.000000, 1.000000, 1 );
    vertices.emplace_back( -1.000000, 1.000000, -1.000000, 1 );
    vertices.emplace_back( -1.000000, -1.000000, -1.000000, 1 );
    vertices.emplace_back( -1.000000, 1.000000, 1.000000, 1 );
    vertices.emplace_back( -1.000000, -1.000000, 1.000000, 1 );

    colours.emplace_back(Colour::white());
    colours.emplace_back(Colour::white());
    colours.emplace_back(Colour::white());
    colours.emplace_back(Colour::white());
    colours.emplace_back(Colour::white());
    colours.emplace_back(Colour::white());
    colours.emplace_back(Colour::white());
    colours.emplace_back(Colour::white());
    
    normals.emplace_back( 0.5774, 0.5773, -0.5773 );
    normals.emplace_back( 0.5773, -0.5774, -0.5774 );
    normals.emplace_back( 0.5773, 0.5774, 0.5774 );
    normals.emplace_back( 0.5774, -0.5773, 0.5773 );
    normals.emplace_back( -0.5773, 0.5774, -0.5774 );
    normals.emplace_back( -0.5774, -0.5773, -0.5773 );
    normals.emplace_back( -0.5774, 0.5773, 0.5773 );
    normals.emplace_back( -0.5773, -0.5774, 0.5774 );

    us.emplace_back(0.875000); vs.emplace_back(0.500000);
    us.emplace_back(0.625000); vs.emplace_back(0.750000);
    us.emplace_back(0.625000); vs.emplace_back(0.500000);
    us.emplace_back(0.375000); vs.emplace_back(1.000000);
    us.emplace_back(0.375000); vs.emplace_back(0.750000);
    us.emplace_back(0.625000); vs.emplace_back(0.000000);
    us.emplace_back(0.375000); vs.emplace_back(0.250000);
    us.emplace_back(0.375000); vs.emplace_back(0.000000);
    us.emplace_back(0.375000); vs.emplace_back(0.500000);
    us.emplace_back(0.125000); vs.emplace_back(0.750000);
    us.emplace_back(0.125000); vs.emplace_back(0.500000);
    us.emplace_back(0.625000); vs.emplace_back(0.250000);
    us.emplace_back(0.875000); vs.emplace_back(0.750000);
    us.emplace_back(0.625000); vs.emplace_back(1.000000);


    indexBuffer.emplace_back(Index{5, 1, 1,  5}); indexBuffer.emplace_back(Index{3, 1, 2, 3}); indexBuffer.emplace_back(Index{1, 1, 3, 1});
    indexBuffer.emplace_back(Index{3, 1, 2,  3}); indexBuffer.emplace_back(Index{8, 1, 4, 8}); indexBuffer.emplace_back(Index{4, 1, 5, 4});
    indexBuffer.emplace_back(Index{7, 1, 6,  7}); indexBuffer.emplace_back(Index{6, 1, 7, 6}); indexBuffer.emplace_back(Index{8, 1, 8, 8});
    indexBuffer.emplace_back(Index{2, 1, 9,  2}); indexBuffer.emplace_back(Index{8, 1, 10, 8}); indexBuffer.emplace_back(Index{6, 1, 11, 6});
    indexBuffer.emplace_back(Index{1, 1, 3,  1}); indexBuffer.emplace_back(Index{4, 1, 5, 4}); indexBuffer.emplace_back(Index{2, 1, 9, 2});
    indexBuffer.emplace_back(Index{5, 1, 12, 5}); indexBuffer.emplace_back(Index{2, 1, 9, 2}); indexBuffer.emplace_back(Index{6, 1, 7, 6});
    indexBuffer.emplace_back(Index{5, 1, 1,  5}); indexBuffer.emplace_back(Index{7, 1, 13, 7}); indexBuffer.emplace_back(Index{3, 1, 2, 3});
    indexBuffer.emplace_back(Index{3, 1, 2,  3}); indexBuffer.emplace_back(Index{7, 1, 14, 7}); indexBuffer.emplace_back(Index{8, 1, 4, 8});
    indexBuffer.emplace_back(Index{7, 1, 6,  7}); indexBuffer.emplace_back(Index{5, 1, 12, 5}); indexBuffer.emplace_back(Index{6, 1, 7, 6});
    indexBuffer.emplace_back(Index{2, 1, 9,  2}); indexBuffer.emplace_back(Index{4, 1, 5, 4}); indexBuffer.emplace_back(Index{8, 1, 10, 8});
    indexBuffer.emplace_back(Index{1, 1, 3,  1}); indexBuffer.emplace_back(Index{3, 1, 2, 3}); indexBuffer.emplace_back(Index{4, 1, 5, 4});
    indexBuffer.emplace_back(Index{5, 1, 12, 5}); indexBuffer.emplace_back(Index{1, 1, 3, 1}); indexBuffer.emplace_back(Index{2, 1, 9, 2});    

    for (int i = 0; i < normals.size(); i++)
        vertexBuffer.emplace_back(vertices[i], colours[i], normals[i], us[i], vs[i]);
    for (int i = normals.size(); i < us.size(); i++)
        vertexBuffer.emplace_back(Vector{-1, -1, -1, -1}, Colour{-1, -1, -1, -1}, Vector{-1, -1, -1}, us[i], vs[i]);

    for (Index& i : indexBuffer) {
        i.colour--;
        i.normal--;
        i.position--;
        i.uv--;
    }
    
    return new Mesh(indexBuffer, vertexBuffer);
}
