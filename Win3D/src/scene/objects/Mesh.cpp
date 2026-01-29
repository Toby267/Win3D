#include "scene/objects/Mesh.hpp"
#include "renderer/Ray.hpp"
#include "scene/dataStructures/BvhNode.hpp"
#include "scene/objects/Materials.hpp"
#include "scene/core/SceneUtil.hpp"
#include "util/Util.hpp"

#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mesh::Mesh(IndexBuffer ib, VertexBuffer vb)
    : VERTEX_BUFFER(vb), indexBuffer(ib), vertexBuffer(vb)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ GETTERS/SETTERS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<Triangle> Mesh::getTriangles() const {
    std::vector<Triangle> triangles;
    triangles.reserve(indexBuffer.size());

    for (int i = 2; i < indexBuffer.size(); i += 3) {
        triangles.emplace_back(
            vertexBuffer[indexBuffer[i-2]],
            vertexBuffer[indexBuffer[i-1]],
            vertexBuffer[indexBuffer[i]]
        );
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

void Mesh::reset() {
    vertexBuffer = VERTEX_BUFFER;
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

Mesh* Mesh::triangle() {
    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> normals;
    
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;

    vertices.emplace_back(-1, -1, -1, 1);
    vertices.emplace_back(0,  1, 1, 1);
    vertices.emplace_back( 1, -1, -1, 1);

    normals.emplace_back( 0.0, 0.0, 1 );
    normals.emplace_back( 0.0, 0.0, 1 );
    normals.emplace_back( 0.0, 0.0, 1 );

    colours.emplace_back(Colour::red());
    colours.emplace_back(Colour::green());
    colours.emplace_back(Colour::blue());
    
    indexBuffer.emplace_back(1);
    indexBuffer.emplace_back(2);
    indexBuffer.emplace_back(3);

    for (int i = 0; i < normals.size(); i++)
        vertexBuffer.emplace_back(vertices[i], colours[i], normals[i]);

    for (size_t& i : indexBuffer)
        i--;

    return new Mesh(indexBuffer, vertexBuffer);
}

Mesh* Mesh::cube() {
    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> normals;

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

    colours.emplace_back(Colour::red());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::blue());
    colours.emplace_back(Colour::green());
    
    normals.emplace_back( 0.5774, 0.5773, -0.5773 );
    normals.emplace_back( 0.5773, -0.5774, -0.5774 );
    normals.emplace_back( 0.5773, 0.5774, 0.5774 );
    normals.emplace_back( 0.5774, -0.5773, 0.5773 );
    normals.emplace_back( -0.5773, 0.5774, -0.5774 );
    normals.emplace_back( -0.5774, -0.5773, -0.5773 );
    normals.emplace_back( -0.5774, 0.5773, 0.5773 );
    normals.emplace_back( -0.5773, -0.5774, 0.5774 );

    indexBuffer.emplace_back(5); indexBuffer.emplace_back(3); indexBuffer.emplace_back(1);
    indexBuffer.emplace_back(3); indexBuffer.emplace_back(8); indexBuffer.emplace_back(4);
    indexBuffer.emplace_back(7); indexBuffer.emplace_back(6); indexBuffer.emplace_back(8);
    indexBuffer.emplace_back(2); indexBuffer.emplace_back(8); indexBuffer.emplace_back(6);
    indexBuffer.emplace_back(1); indexBuffer.emplace_back(4); indexBuffer.emplace_back(2);
    indexBuffer.emplace_back(5); indexBuffer.emplace_back(2); indexBuffer.emplace_back(6);
    indexBuffer.emplace_back(5); indexBuffer.emplace_back(7); indexBuffer.emplace_back(3);
    indexBuffer.emplace_back(3); indexBuffer.emplace_back(7); indexBuffer.emplace_back(8);
    indexBuffer.emplace_back(7); indexBuffer.emplace_back(5); indexBuffer.emplace_back(6);
    indexBuffer.emplace_back(2); indexBuffer.emplace_back(4); indexBuffer.emplace_back(8);
    indexBuffer.emplace_back(1); indexBuffer.emplace_back(3); indexBuffer.emplace_back(4);
    indexBuffer.emplace_back(5); indexBuffer.emplace_back(1); indexBuffer.emplace_back(2);

    for (int i = 0; i < normals.size(); i++)
        vertexBuffer.emplace_back(vertices[i], colours[i], normals[i]);

    for (size_t& i : indexBuffer)
        i--;
    
    return new Mesh(indexBuffer, vertexBuffer);
}
    
// Mesh* Mesh::sphere() {
//     std::vector<Vector> vertices;
//     std::vector<Colour> colours;
//     std::vector<Vector> normals;

//     VertexBuffer vertexBuffer;
//     IndexBuffer indexBuffer;

//     vertices.emplace_back( 0.000000, -1.000000, 0.000000, 1 );
//     vertices.emplace_back( 0.723607, -0.447220, 0.525725, 1 );
//     vertices.emplace_back( -0.276388, -0.447220, 0.850649, 1 );
//     vertices.emplace_back( -0.894426, -0.447216, 0.000000, 1 );
//     vertices.emplace_back( -0.276388, -0.447220, -0.850649, 1 );
//     vertices.emplace_back( 0.723607, -0.447220, -0.525725, 1 );
//     vertices.emplace_back( 0.276388, 0.447220, 0.850649, 1 );
//     vertices.emplace_back( -0.723607, 0.447220, 0.525725, 1 );
//     vertices.emplace_back( -0.723607, 0.447220, -0.525725, 1 );
//     vertices.emplace_back( 0.276388, 0.447220, -0.850649, 1 );
//     vertices.emplace_back( 0.894426, 0.447216, 0.000000, 1 );
//     vertices.emplace_back( 0.000000, 1.000000, 0.000000, 1 );
//     vertices.emplace_back( -0.232822, -0.657519, 0.716563, 1 );
//     vertices.emplace_back( -0.162456, -0.850654, 0.499995, 1 );
//     vertices.emplace_back( -0.077607, -0.967950, 0.238853, 1 );
//     vertices.emplace_back( 0.203181, -0.967950, 0.147618, 1 );
//     vertices.emplace_back( 0.425323, -0.850654, 0.309011, 1 );
//     vertices.emplace_back( 0.609547, -0.657519, 0.442856, 1 );
//     vertices.emplace_back( 0.531941, -0.502302, 0.681712, 1 );
//     vertices.emplace_back( 0.262869, -0.525738, 0.809012, 1 );
//     vertices.emplace_back( -0.029639, -0.502302, 0.864184, 1 );
//     vertices.emplace_back( 0.812729, -0.502301, -0.295238, 1 );
//     vertices.emplace_back( 0.850648, -0.525736, 0.000000, 1 );
//     vertices.emplace_back( 0.812729, -0.502301, 0.295238, 1 );
//     vertices.emplace_back( 0.203181, -0.967950, -0.147618, 1 );
//     vertices.emplace_back( 0.425323, -0.850654, -0.309011, 1 );
//     vertices.emplace_back( 0.609547, -0.657519, -0.442856, 1 );
//     vertices.emplace_back( -0.753442, -0.657515, 0.000000, 1 );
//     vertices.emplace_back( -0.525730, -0.850652, 0.000000, 1 );
//     vertices.emplace_back( -0.251147, -0.967949, 0.000000, 1 );
//     vertices.emplace_back( -0.483971, -0.502302, 0.716565, 1 );
//     vertices.emplace_back( -0.688189, -0.525736, 0.499997, 1 );
//     vertices.emplace_back( -0.831051, -0.502299, 0.238853, 1 );
//     vertices.emplace_back( -0.232822, -0.657519, -0.716563, 1 );
//     vertices.emplace_back( -0.162456, -0.850654, -0.499995, 1 );
//     vertices.emplace_back( -0.077607, -0.967950, -0.238853, 1 );
//     vertices.emplace_back( -0.831051, -0.502299, -0.238853, 1 );
//     vertices.emplace_back( -0.688189, -0.525736, -0.499997, 1 );
//     vertices.emplace_back( -0.483971, -0.502302, -0.716565, 1 );
//     vertices.emplace_back( -0.029639, -0.502302, -0.864184, 1 );
//     vertices.emplace_back( 0.262869, -0.525738, -0.809012, 1 );
//     vertices.emplace_back( 0.531941, -0.502302, -0.681712, 1 );
//     vertices.emplace_back( 0.956626, 0.251149, 0.147618, 1 );
//     vertices.emplace_back( 0.951058, -0.000000, 0.309013, 1 );
//     vertices.emplace_back( 0.860698, -0.251151, 0.442858, 1 );
//     vertices.emplace_back( 0.860698, -0.251151, -0.442858, 1 );
//     vertices.emplace_back( 0.951058, 0.000000, -0.309013, 1 );
//     vertices.emplace_back( 0.956626, 0.251149, -0.147618, 1 );
//     vertices.emplace_back( 0.155215, 0.251152, 0.955422, 1 );
//     vertices.emplace_back( 0.000000, -0.000000, 1.000000, 1 );
//     vertices.emplace_back( -0.155215, -0.251152, 0.955422, 1 );
//     vertices.emplace_back( 0.687159, -0.251152, 0.681715, 1 );
//     vertices.emplace_back( 0.587786, 0.000000, 0.809017, 1 );
//     vertices.emplace_back( 0.436007, 0.251152, 0.864188, 1 );
//     vertices.emplace_back( -0.860698, 0.251151, 0.442858, 1 );
//     vertices.emplace_back( -0.951058, -0.000000, 0.309013, 1 );
//     vertices.emplace_back( -0.956626, -0.251149, 0.147618, 1 );
//     vertices.emplace_back( -0.436007, -0.251152, 0.864188, 1 );
//     vertices.emplace_back( -0.587786, 0.000000, 0.809017, 1 );
//     vertices.emplace_back( -0.687159, 0.251152, 0.681715, 1 );
//     vertices.emplace_back( -0.687159, 0.251152, -0.681715, 1 );
//     vertices.emplace_back( -0.587786, -0.000000, -0.809017, 1 );
//     vertices.emplace_back( -0.436007, -0.251152, -0.864188, 1 );
//     vertices.emplace_back( -0.956626, -0.251149, -0.147618, 1 );
//     vertices.emplace_back( -0.951058, 0.000000, -0.309013, 1 );
//     vertices.emplace_back( -0.860698, 0.251151, -0.442858, 1 );
//     vertices.emplace_back( 0.436007, 0.251152, -0.864188, 1 );
//     vertices.emplace_back( 0.587786, -0.000000, -0.809017, 1 );
//     vertices.emplace_back( 0.687159, -0.251152, -0.681715, 1 );
//     vertices.emplace_back( -0.155215, -0.251152, -0.955422, 1 );
//     vertices.emplace_back( 0.000000, 0.000000, -1.000000, 1 );
//     vertices.emplace_back( 0.155215, 0.251152, -0.955422, 1 );
//     vertices.emplace_back( 0.831051, 0.502299, 0.238853, 1 );
//     vertices.emplace_back( 0.688189, 0.525736, 0.499997, 1 );
//     vertices.emplace_back( 0.483971, 0.502302, 0.716565, 1 );
//     vertices.emplace_back( 0.029639, 0.502302, 0.864184, 1 );
//     vertices.emplace_back( -0.262869, 0.525738, 0.809012, 1 );
//     vertices.emplace_back( -0.531941, 0.502302, 0.681712, 1 );
//     vertices.emplace_back( -0.812729, 0.502301, 0.295238, 1 );
//     vertices.emplace_back( -0.850648, 0.525736, 0.000000, 1 );
//     vertices.emplace_back( -0.812729, 0.502301, -0.295238, 1 );
//     vertices.emplace_back( -0.531941, 0.502302, -0.681712, 1 );
//     vertices.emplace_back( -0.262869, 0.525738, -0.809012, 1 );
//     vertices.emplace_back( 0.029639, 0.502302, -0.864184, 1 );
//     vertices.emplace_back( 0.483971, 0.502302, -0.716565, 1 );
//     vertices.emplace_back( 0.688189, 0.525736, -0.499997, 1 );
//     vertices.emplace_back( 0.831051, 0.502299, -0.238853, 1 );
//     vertices.emplace_back( 0.077607, 0.967950, 0.238853, 1 );
//     vertices.emplace_back( 0.162456, 0.850654, 0.499995, 1 );
//     vertices.emplace_back( 0.232822, 0.657519, 0.716563, 1 );
//     vertices.emplace_back( 0.753442, 0.657515, 0.000000, 1 );
//     vertices.emplace_back( 0.525730, 0.850652, 0.000000, 1 );
//     vertices.emplace_back( 0.251147, 0.967949, 0.000000, 1 );
//     vertices.emplace_back( -0.203181, 0.967950, 0.147618, 1 );
//     vertices.emplace_back( -0.425323, 0.850654, 0.309011, 1 );
//     vertices.emplace_back( -0.609547, 0.657519, 0.442856, 1 );
//     vertices.emplace_back( -0.203181, 0.967950, -0.147618, 1 );
//     vertices.emplace_back( -0.425323, 0.850654, -0.309011, 1 );
//     vertices.emplace_back( -0.609547, 0.657519, -0.442856, 1 );
//     vertices.emplace_back( 0.077607, 0.967950, -0.238853, 1 );
//     vertices.emplace_back( 0.162456, 0.850654, -0.499995, 1 );
//     vertices.emplace_back( 0.232822, 0.657519, -0.716563, 1 );
//     vertices.emplace_back( 0.361800, 0.894429, -0.262863, 1 );
//     vertices.emplace_back( 0.638194, 0.723610, -0.262864, 1 );
//     vertices.emplace_back( 0.447209, 0.723612, -0.525728, 1 );
//     vertices.emplace_back( -0.138197, 0.894430, -0.425319, 1 );
//     vertices.emplace_back( -0.052790, 0.723612, -0.688185, 1 );
//     vertices.emplace_back( -0.361804, 0.723612, -0.587778, 1 );
//     vertices.emplace_back( -0.447210, 0.894429, 0.000000, 1 );
//     vertices.emplace_back( -0.670817, 0.723611, -0.162457, 1 );
//     vertices.emplace_back( -0.670817, 0.723611, 0.162457, 1 );
//     vertices.emplace_back( -0.138197, 0.894430, 0.425319, 1 );
//     vertices.emplace_back( -0.361804, 0.723612, 0.587778, 1 );
//     vertices.emplace_back( -0.052790, 0.723612, 0.688185, 1 );
//     vertices.emplace_back( 0.361800, 0.894429, 0.262863, 1 );
//     vertices.emplace_back( 0.447209, 0.723612, 0.525728, 1 );
//     vertices.emplace_back( 0.638194, 0.723610, 0.262864, 1 );
//     vertices.emplace_back( 0.861804, 0.276396, -0.425322, 1 );
//     vertices.emplace_back( 0.809019, 0.000000, -0.587782, 1 );
//     vertices.emplace_back( 0.670821, 0.276397, -0.688189, 1 );
//     vertices.emplace_back( -0.138199, 0.276397, -0.951055, 1 );
//     vertices.emplace_back( -0.309016, -0.000000, -0.951057, 1 );
//     vertices.emplace_back( -0.447215, 0.276397, -0.850649, 1 );
//     vertices.emplace_back( -0.947213, 0.276396, -0.162458, 1 );
//     vertices.emplace_back( -1.000000, 0.000001, 0.000000, 1 );
//     vertices.emplace_back( -0.947213, 0.276397, 0.162458, 1 );
//     vertices.emplace_back( -0.447216, 0.276397, 0.850648, 1 );
//     vertices.emplace_back( -0.309017, -0.000001, 0.951056, 1 );
//     vertices.emplace_back( -0.138199, 0.276397, 0.951055, 1 );
//     vertices.emplace_back( 0.670820, 0.276396, 0.688190, 1 );
//     vertices.emplace_back( 0.809019, -0.000002, 0.587783, 1 );
//     vertices.emplace_back( 0.861804, 0.276394, 0.425323, 1 );
//     vertices.emplace_back( 0.309017, -0.000000, -0.951056, 1 );
//     vertices.emplace_back( 0.447216, -0.276398, -0.850648, 1 );
//     vertices.emplace_back( 0.138199, -0.276398, -0.951055, 1 );
//     vertices.emplace_back( -0.809018, -0.000000, -0.587783, 1 );
//     vertices.emplace_back( -0.670819, -0.276397, -0.688191, 1 );
//     vertices.emplace_back( -0.861803, -0.276396, -0.425324, 1 );
//     vertices.emplace_back( -0.809018, 0.000000, 0.587783, 1 );
//     vertices.emplace_back( -0.861803, -0.276396, 0.425324, 1 );
//     vertices.emplace_back( -0.670819, -0.276397, 0.688191, 1 );
//     vertices.emplace_back( 0.309017, 0.000000, 0.951056, 1 );
//     vertices.emplace_back( 0.138199, -0.276398, 0.951055, 1 );
//     vertices.emplace_back( 0.447216, -0.276398, 0.850648, 1 );
//     vertices.emplace_back( 1.000000, 0.000000, 0.000000, 1 );
//     vertices.emplace_back( 0.947213, -0.276396, 0.162458, 1 );
//     vertices.emplace_back( 0.947213, -0.276396, -0.162458, 1 );
//     vertices.emplace_back( 0.361803, -0.723612, -0.587779, 1 );
//     vertices.emplace_back( 0.138197, -0.894429, -0.425321, 1 );
//     vertices.emplace_back( 0.052789, -0.723611, -0.688186, 1 );
//     vertices.emplace_back( -0.447211, -0.723612, -0.525727, 1 );
//     vertices.emplace_back( -0.361801, -0.894429, -0.262863, 1 );
//     vertices.emplace_back( -0.638195, -0.723609, -0.262863, 1 );
//     vertices.emplace_back( -0.638195, -0.723609, 0.262864, 1 );
//     vertices.emplace_back( -0.361801, -0.894428, 0.262864, 1 );
//     vertices.emplace_back( -0.447211, -0.723610, 0.525729, 1 );
//     vertices.emplace_back( 0.670817, -0.723611, -0.162457, 1 );
//     vertices.emplace_back( 0.670818, -0.723610, 0.162458, 1 );
//     vertices.emplace_back( 0.447211, -0.894428, 0.000001, 1 );
//     vertices.emplace_back( 0.052790, -0.723612, 0.688185, 1 );
//     vertices.emplace_back( 0.138199, -0.894429, 0.425321, 1 );
//     vertices.emplace_back( 0.361805, -0.723611, 0.587779, 1 );

//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());
//     colours.emplace_back(Colour::blue());

//     normals.emplace_back( -0.0000, -1.0000, -0.0000 );
//     normals.emplace_back( 0.7236, -0.4472, 0.5257 );
//     normals.emplace_back( -0.2764, -0.4472, 0.8506 );
//     normals.emplace_back( -0.8944, -0.4472, -0.0000 );
//     normals.emplace_back( -0.2764, -0.4472, -0.8506 );
//     normals.emplace_back( 0.7236, -0.4472, -0.5257 );
//     normals.emplace_back( 0.2764, 0.4472, 0.8506 );
//     normals.emplace_back( -0.7236, 0.4472, 0.5257 );
//     normals.emplace_back( -0.7236, 0.4472, -0.5257 );
//     normals.emplace_back( 0.2764, 0.4472, -0.8506 );
//     normals.emplace_back( 0.8944, 0.4472, -0.0000 );
//     normals.emplace_back( -0.0000, 1.0000, -0.0000 );
//     normals.emplace_back( -0.2308, -0.6650, 0.7103 );
//     normals.emplace_back( -0.1625, -0.8507, 0.5000 );
//     normals.emplace_back( -0.0806, -0.9654, 0.2480 );
//     normals.emplace_back( 0.2110, -0.9654, 0.1533 );
//     normals.emplace_back( 0.4253, -0.8507, 0.3090 );
//     normals.emplace_back( 0.6042, -0.6650, 0.4390 );
//     normals.emplace_back( 0.5237, -0.5038, 0.6870 );
//     normals.emplace_back( 0.2629, -0.5257, 0.8090 );
//     normals.emplace_back( -0.0198, -0.5038, 0.8636 );
//     normals.emplace_back( 0.8152, -0.5038, -0.2857 );
//     normals.emplace_back( 0.8506, -0.5257, -0.0000 );
//     normals.emplace_back( 0.8152, -0.5038, 0.2857 );
//     normals.emplace_back( 0.2110, -0.9654, -0.1533 );
//     normals.emplace_back( 0.4253, -0.8507, -0.3090 );
//     normals.emplace_back( 0.6042, -0.6650, -0.4390 );
//     normals.emplace_back( -0.7469, -0.6650, -0.0000 );
//     normals.emplace_back( -0.5257, -0.8507, -0.0000 );
//     normals.emplace_back( -0.2608, -0.9654, -0.0000 );
//     normals.emplace_back( -0.4915, -0.5038, 0.7103 );
//     normals.emplace_back( -0.6882, -0.5257, 0.5000 );
//     normals.emplace_back( -0.8274, -0.5038, 0.2480 );
//     normals.emplace_back( -0.2308, -0.6650, -0.7103 );
//     normals.emplace_back( -0.1625, -0.8507, -0.5000 );
//     normals.emplace_back( -0.0806, -0.9654, -0.2480 );
//     normals.emplace_back( -0.8274, -0.5038, -0.2480 );
//     normals.emplace_back( -0.6882, -0.5257, -0.5000 );
//     normals.emplace_back( -0.4915, -0.5038, -0.7103 );
//     normals.emplace_back( -0.0198, -0.5038, -0.8636 );
//     normals.emplace_back( 0.2629, -0.5257, -0.8090 );
//     normals.emplace_back( 0.5237, -0.5038, -0.6870 );
//     normals.emplace_back( 0.9578, 0.2431, 0.1533 );
//     normals.emplace_back( 0.9511, -0.0000, 0.3090 );
//     normals.emplace_back( 0.8650, -0.2431, 0.4390 );
//     normals.emplace_back( 0.8650, -0.2431, -0.4390 );
//     normals.emplace_back( 0.9511, -0.0000, -0.3090 );
//     normals.emplace_back( 0.9578, 0.2431, -0.1533 );
//     normals.emplace_back( 0.1502, 0.2431, 0.9583 );
//     normals.emplace_back( -0.0000, -0.0000, 1.0000 );
//     normals.emplace_back( -0.1502, -0.2431, 0.9583 );
//     normals.emplace_back( 0.6848, -0.2431, 0.6870 );
//     normals.emplace_back( 0.5878, -0.0000, 0.8090 );
//     normals.emplace_back( 0.4417, 0.2431, 0.8636 );
//     normals.emplace_back( -0.8650, 0.2431, 0.4390 );
//     normals.emplace_back( -0.9511, -0.0000, 0.3090 );
//     normals.emplace_back( -0.9578, -0.2431, 0.1533 );
//     normals.emplace_back( -0.4417, -0.2431, 0.8636 );
//     normals.emplace_back( -0.5878, -0.0000, 0.8090 );
//     normals.emplace_back( -0.6848, 0.2431, 0.6870 );
//     normals.emplace_back( -0.6848, 0.2431, -0.6870 );
//     normals.emplace_back( -0.5878, -0.0000, -0.8090 );
//     normals.emplace_back( -0.4417, -0.2431, -0.8636 );
//     normals.emplace_back( -0.9578, -0.2431, -0.1533 );
//     normals.emplace_back( -0.9511, -0.0000, -0.3090 );
//     normals.emplace_back( -0.8650, 0.2431, -0.4390 );
//     normals.emplace_back( 0.4417, 0.2431, -0.8636 );
//     normals.emplace_back( 0.5878, -0.0000, -0.8090 );
//     normals.emplace_back( 0.6848, -0.2431, -0.6870 );
//     normals.emplace_back( -0.1502, -0.2431, -0.9583 );
//     normals.emplace_back( -0.0000, -0.0000, -1.0000 );
//     normals.emplace_back( 0.1502, 0.2431, -0.9583 );
//     normals.emplace_back( 0.8274, 0.5038, 0.2480 );
//     normals.emplace_back( 0.6882, 0.5257, 0.5000 );
//     normals.emplace_back( 0.4915, 0.5038, 0.7103 );
//     normals.emplace_back( 0.0198, 0.5038, 0.8636 );
//     normals.emplace_back( -0.2629, 0.5257, 0.8090 );
//     normals.emplace_back( -0.5237, 0.5038, 0.6870 );
//     normals.emplace_back( -0.8152, 0.5038, 0.2857 );
//     normals.emplace_back( -0.8506, 0.5257, -0.0000 );
//     normals.emplace_back( -0.8152, 0.5038, -0.2857 );
//     normals.emplace_back( -0.5237, 0.5038, -0.6870 );
//     normals.emplace_back( -0.2629, 0.5257, -0.8090 );
//     normals.emplace_back( 0.0198, 0.5038, -0.8636 );
//     normals.emplace_back( 0.4915, 0.5038, -0.7103 );
//     normals.emplace_back( 0.6882, 0.5257, -0.5000 );
//     normals.emplace_back( 0.8274, 0.5038, -0.2480 );
//     normals.emplace_back( 0.0806, 0.9654, 0.2480 );
//     normals.emplace_back( 0.1625, 0.8507, 0.5000 );
//     normals.emplace_back( 0.2308, 0.6650, 0.7103 );
//     normals.emplace_back( 0.7469, 0.6650, -0.0000 );
//     normals.emplace_back( 0.5257, 0.8507, -0.0000 );
//     normals.emplace_back( 0.2607, 0.9654, -0.0000 );
//     normals.emplace_back( -0.2110, 0.9654, 0.1533 );
//     normals.emplace_back( -0.4253, 0.8507, 0.3090 );
//     normals.emplace_back( -0.6042, 0.6650, 0.4390 );
//     normals.emplace_back( -0.2110, 0.9654, -0.1533 );
//     normals.emplace_back( -0.4253, 0.8507, -0.3090 );
//     normals.emplace_back( -0.6042, 0.6650, -0.4390 );
//     normals.emplace_back( 0.0806, 0.9654, -0.2480 );
//     normals.emplace_back( 0.1625, 0.8507, -0.5000 );
//     normals.emplace_back( 0.2308, 0.6650, -0.7103 );
//     normals.emplace_back( 0.3682, 0.8904, -0.2675 );
//     normals.emplace_back( 0.6317, 0.7275, -0.2675 );
//     normals.emplace_back( 0.4496, 0.7276, -0.5182 );
//     normals.emplace_back( -0.1406, 0.8904, -0.4329 );
//     normals.emplace_back( -0.0592, 0.7276, -0.6835 );
//     normals.emplace_back( -0.3539, 0.7276, -0.5878 );
//     normals.emplace_back( -0.4551, 0.8904, -0.0000 );
//     normals.emplace_back( -0.6683, 0.7276, -0.1549 );
//     normals.emplace_back( -0.6683, 0.7276, 0.1549 );
//     normals.emplace_back( -0.1406, 0.8904, 0.4329 );
//     normals.emplace_back( -0.3539, 0.7276, 0.5878 );
//     normals.emplace_back( -0.0592, 0.7276, 0.6835 );
//     normals.emplace_back( 0.3682, 0.8904, 0.2675 );
//     normals.emplace_back( 0.4496, 0.7276, 0.5182 );
//     normals.emplace_back( 0.6317, 0.7275, 0.2675 );
//     normals.emplace_back( 0.8593, 0.2724, -0.4329 );
//     normals.emplace_back( 0.8090, 0.0089, -0.5878 );
//     normals.emplace_back( 0.6772, 0.2724, -0.6835 );
//     normals.emplace_back( -0.1461, 0.2724, -0.9510 );
//     normals.emplace_back( -0.3090, 0.0089, -0.9510 );
//     normals.emplace_back( -0.4408, 0.2724, -0.8553 );
//     normals.emplace_back( -0.9496, 0.2724, -0.1549 );
//     normals.emplace_back( -1.0000, 0.0089, -0.0000 );
//     normals.emplace_back( -0.9496, 0.2724, 0.1549 );
//     normals.emplace_back( -0.4408, 0.2724, 0.8553 );
//     normals.emplace_back( -0.3090, 0.0089, 0.9510 );
//     normals.emplace_back( -0.1461, 0.2724, 0.9510 );
//     normals.emplace_back( 0.6772, 0.2724, 0.6835 );
//     normals.emplace_back( 0.8090, 0.0089, 0.5878 );
//     normals.emplace_back( 0.8593, 0.2724, 0.4329 );
//     normals.emplace_back( 0.3090, -0.0089, -0.9510 );
//     normals.emplace_back( 0.4408, -0.2724, -0.8553 );
//     normals.emplace_back( 0.1461, -0.2724, -0.9510 );
//     normals.emplace_back( -0.8090, -0.0089, -0.5878 );
//     normals.emplace_back( -0.6772, -0.2724, -0.6835 );
//     normals.emplace_back( -0.8593, -0.2724, -0.4329 );
//     normals.emplace_back( -0.8090, -0.0089, 0.5878 );
//     normals.emplace_back( -0.8593, -0.2724, 0.4329 );
//     normals.emplace_back( -0.6772, -0.2724, 0.6835 );
//     normals.emplace_back( 0.3090, -0.0089, 0.9510 );
//     normals.emplace_back( 0.1461, -0.2724, 0.9510 );
//     normals.emplace_back( 0.4408, -0.2724, 0.8553 );
//     normals.emplace_back( 1.0000, -0.0089, -0.0000 );
//     normals.emplace_back( 0.9496, -0.2724, 0.1549 );
//     normals.emplace_back( 0.9496, -0.2724, -0.1549 );
//     normals.emplace_back( 0.3539, -0.7276, -0.5878 );
//     normals.emplace_back( 0.1406, -0.8904, -0.4329 );
//     normals.emplace_back( 0.0592, -0.7276, -0.6835 );
//     normals.emplace_back( -0.4496, -0.7276, -0.5182 );
//     normals.emplace_back( -0.3682, -0.8904, -0.2675 );
//     normals.emplace_back( -0.6317, -0.7275, -0.2675 );
//     normals.emplace_back( -0.6317, -0.7275, 0.2675 );
//     normals.emplace_back( -0.3682, -0.8904, 0.2675 );
//     normals.emplace_back( -0.4496, -0.7275, 0.5182 );
//     normals.emplace_back( 0.6683, -0.7275, -0.1549 );
//     normals.emplace_back( 0.6683, -0.7275, 0.1549 );
//     normals.emplace_back( 0.4551, -0.8904, -0.0000 );
//     normals.emplace_back( 0.0592, -0.7276, 0.6835 );
//     normals.emplace_back( 0.1406, -0.8904, 0.4329 );
//     normals.emplace_back( 0.3539, -0.7276, 0.5878 );

//     indexBuffer.emplace_back( 1, 16, 15 );
//     indexBuffer.emplace_back( 2, 18, 24 );
//     indexBuffer.emplace_back( 1, 15, 30 );
//     indexBuffer.emplace_back( 1, 30, 36 );
//     indexBuffer.emplace_back( 1, 36, 25 );
//     indexBuffer.emplace_back( 2, 24, 45 );
//     indexBuffer.emplace_back( 3, 21, 51 );
//     indexBuffer.emplace_back( 4, 33, 57 );
//     indexBuffer.emplace_back( 5, 39, 63 );
//     indexBuffer.emplace_back( 6, 42, 69 );
//     indexBuffer.emplace_back( 2, 45, 52 );
//     indexBuffer.emplace_back( 3, 51, 58 );
//     indexBuffer.emplace_back( 4, 57, 64 );
//     indexBuffer.emplace_back( 5, 63, 70 );
//     indexBuffer.emplace_back( 6, 69, 46 );
//     indexBuffer.emplace_back( 7, 75, 90 );
//     indexBuffer.emplace_back( 8, 78, 96 );
//     indexBuffer.emplace_back( 9, 81, 99 );
//     indexBuffer.emplace_back( 10, 84, 102 );
//     indexBuffer.emplace_back( 11, 87, 91 );
//     indexBuffer.emplace_back( 93, 100, 12 );
//     indexBuffer.emplace_back( 92, 103, 93 );
//     indexBuffer.emplace_back( 91, 104, 92 );
//     indexBuffer.emplace_back( 93, 103, 100 );
//     indexBuffer.emplace_back( 103, 101, 100 );
//     indexBuffer.emplace_back( 92, 104, 103 );
//     indexBuffer.emplace_back( 104, 105, 103 );
//     indexBuffer.emplace_back( 103, 105, 101 );
//     indexBuffer.emplace_back( 105, 102, 101 );
//     indexBuffer.emplace_back( 91, 87, 104 );
//     indexBuffer.emplace_back( 87, 86, 104 );
//     indexBuffer.emplace_back( 104, 86, 105 );
//     indexBuffer.emplace_back( 86, 85, 105 );
//     indexBuffer.emplace_back( 105, 85, 102 );
//     indexBuffer.emplace_back( 85, 10, 102 );
//     indexBuffer.emplace_back( 100, 97, 12 );
//     indexBuffer.emplace_back( 101, 106, 100 );
//     indexBuffer.emplace_back( 102, 107, 101 );
//     indexBuffer.emplace_back( 100, 106, 97 );
//     indexBuffer.emplace_back( 106, 98, 97 );
//     indexBuffer.emplace_back( 101, 107, 106 );
//     indexBuffer.emplace_back( 107, 108, 106 );
//     indexBuffer.emplace_back( 106, 108, 98 );
//     indexBuffer.emplace_back( 108, 99, 98 );
//     indexBuffer.emplace_back( 102, 84, 107 );
//     indexBuffer.emplace_back( 84, 83, 107 );
//     indexBuffer.emplace_back( 107, 83, 108 );
//     indexBuffer.emplace_back( 83, 82, 108 );
//     indexBuffer.emplace_back( 108, 82, 99 );
//     indexBuffer.emplace_back( 82, 9, 99 );
//     indexBuffer.emplace_back( 97, 94, 12 );
//     indexBuffer.emplace_back( 98, 109, 97 );
//     indexBuffer.emplace_back( 99, 110, 98 );
//     indexBuffer.emplace_back( 97, 109, 94 );
//     indexBuffer.emplace_back( 109, 95, 94 );
//     indexBuffer.emplace_back( 98, 110, 109 );
//     indexBuffer.emplace_back( 110, 111, 109 );
//     indexBuffer.emplace_back( 109, 111, 95 );
//     indexBuffer.emplace_back( 111, 96, 95 );
//     indexBuffer.emplace_back( 99, 81, 110 );
//     indexBuffer.emplace_back( 81, 80, 110 );
//     indexBuffer.emplace_back( 110, 80, 111 );
//     indexBuffer.emplace_back( 80, 79, 111 );
//     indexBuffer.emplace_back( 111, 79, 96 );
//     indexBuffer.emplace_back( 79, 8, 96 );
//     indexBuffer.emplace_back( 94, 88, 12 );
//     indexBuffer.emplace_back( 95, 112, 94 );
//     indexBuffer.emplace_back( 96, 113, 95 );
//     indexBuffer.emplace_back( 94, 112, 88 );
//     indexBuffer.emplace_back( 112, 89, 88 );
//     indexBuffer.emplace_back( 95, 113, 112 );
//     indexBuffer.emplace_back( 113, 114, 112 );
//     indexBuffer.emplace_back( 112, 114, 89 );
//     indexBuffer.emplace_back( 114, 90, 89 );
//     indexBuffer.emplace_back( 96, 78, 113 );
//     indexBuffer.emplace_back( 78, 77, 113 );
//     indexBuffer.emplace_back( 113, 77, 114 );
//     indexBuffer.emplace_back( 77, 76, 114 );
//     indexBuffer.emplace_back( 114, 76, 90 );
//     indexBuffer.emplace_back( 76, 7, 90 );
//     indexBuffer.emplace_back( 88, 93, 12 );
//     indexBuffer.emplace_back( 89, 115, 88 );
//     indexBuffer.emplace_back( 90, 116, 89 );
//     indexBuffer.emplace_back( 88, 115, 93 );
//     indexBuffer.emplace_back( 115, 92, 93 );
//     indexBuffer.emplace_back( 89, 116, 115 );
//     indexBuffer.emplace_back( 116, 117, 115 );
//     indexBuffer.emplace_back( 115, 117, 92 );
//     indexBuffer.emplace_back( 117, 91, 92 );
//     indexBuffer.emplace_back( 90, 75, 116 );
//     indexBuffer.emplace_back( 75, 74, 116 );
//     indexBuffer.emplace_back( 116, 74, 117 );
//     indexBuffer.emplace_back( 74, 73, 117 );
//     indexBuffer.emplace_back( 117, 73, 91 );
//     indexBuffer.emplace_back( 73, 11, 91 );
//     indexBuffer.emplace_back( 48, 87, 11 );
//     indexBuffer.emplace_back( 47, 118, 48 );
//     indexBuffer.emplace_back( 46, 119, 47 );
//     indexBuffer.emplace_back( 48, 118, 87 );
//     indexBuffer.emplace_back( 118, 86, 87 );
//     indexBuffer.emplace_back( 47, 119, 118 );
//     indexBuffer.emplace_back( 119, 120, 118 );
//     indexBuffer.emplace_back( 118, 120, 86 );
//     indexBuffer.emplace_back( 120, 85, 86 );
//     indexBuffer.emplace_back( 46, 69, 119 );
//     indexBuffer.emplace_back( 69, 68, 119 );
//     indexBuffer.emplace_back( 119, 68, 120 );
//     indexBuffer.emplace_back( 68, 67, 120 );
//     indexBuffer.emplace_back( 120, 67, 85 );
//     indexBuffer.emplace_back( 67, 10, 85 );
//     indexBuffer.emplace_back( 72, 84, 10 );
//     indexBuffer.emplace_back( 71, 121, 72 );
//     indexBuffer.emplace_back( 70, 122, 71 );
//     indexBuffer.emplace_back( 72, 121, 84 );
//     indexBuffer.emplace_back( 121, 83, 84 );
//     indexBuffer.emplace_back( 71, 122, 121 );
//     indexBuffer.emplace_back( 122, 123, 121 );
//     indexBuffer.emplace_back( 121, 123, 83 );
//     indexBuffer.emplace_back( 123, 82, 83 );
//     indexBuffer.emplace_back( 70, 63, 122 );
//     indexBuffer.emplace_back( 63, 62, 122 );
//     indexBuffer.emplace_back( 122, 62, 123 );
//     indexBuffer.emplace_back( 62, 61, 123 );
//     indexBuffer.emplace_back( 123, 61, 82 );
//     indexBuffer.emplace_back( 61, 9, 82 );
//     indexBuffer.emplace_back( 66, 81, 9 );
//     indexBuffer.emplace_back( 65, 124, 66 );
//     indexBuffer.emplace_back( 64, 125, 65 );
//     indexBuffer.emplace_back( 66, 124, 81 );
//     indexBuffer.emplace_back( 124, 80, 81 );
//     indexBuffer.emplace_back( 65, 125, 124 );
//     indexBuffer.emplace_back( 125, 126, 124 );
//     indexBuffer.emplace_back( 124, 126, 80 );
//     indexBuffer.emplace_back( 126, 79, 80 );
//     indexBuffer.emplace_back( 64, 57, 125 );
//     indexBuffer.emplace_back( 57, 56, 125 );
//     indexBuffer.emplace_back( 125, 56, 126 );
//     indexBuffer.emplace_back( 56, 55, 126 );
//     indexBuffer.emplace_back( 126, 55, 79 );
//     indexBuffer.emplace_back( 55, 8, 79 );
//     indexBuffer.emplace_back( 60, 78, 8 );
//     indexBuffer.emplace_back( 59, 127, 60 );
//     indexBuffer.emplace_back( 58, 128, 59 );
//     indexBuffer.emplace_back( 60, 127, 78 );
//     indexBuffer.emplace_back( 127, 77, 78 );
//     indexBuffer.emplace_back( 59, 128, 127 );
//     indexBuffer.emplace_back( 128, 129, 127 );
//     indexBuffer.emplace_back( 127, 129, 77 );
//     indexBuffer.emplace_back( 129, 76, 77 );
//     indexBuffer.emplace_back( 58, 51, 128 );
//     indexBuffer.emplace_back( 51, 50, 128 );
//     indexBuffer.emplace_back( 128, 50, 129 );
//     indexBuffer.emplace_back( 50, 49, 129 );
//     indexBuffer.emplace_back( 129, 49, 76 );
//     indexBuffer.emplace_back( 49, 7, 76 );
//     indexBuffer.emplace_back( 54, 75, 7 );
//     indexBuffer.emplace_back( 53, 130, 54 );
//     indexBuffer.emplace_back( 52, 131, 53 );
//     indexBuffer.emplace_back( 54, 130, 75 );
//     indexBuffer.emplace_back( 130, 74, 75 );
//     indexBuffer.emplace_back( 53, 131, 130 );
//     indexBuffer.emplace_back( 131, 132, 130 );
//     indexBuffer.emplace_back( 130, 132, 74 );
//     indexBuffer.emplace_back( 132, 73, 74 );
//     indexBuffer.emplace_back( 52, 45, 131 );
//     indexBuffer.emplace_back( 45, 44, 131 );
//     indexBuffer.emplace_back( 131, 44, 132 );
//     indexBuffer.emplace_back( 44, 43, 132 );
//     indexBuffer.emplace_back( 132, 43, 73 );
//     indexBuffer.emplace_back( 43, 11, 73 );
//     indexBuffer.emplace_back( 67, 72, 10 );
//     indexBuffer.emplace_back( 68, 133, 67 );
//     indexBuffer.emplace_back( 69, 134, 68 );
//     indexBuffer.emplace_back( 67, 133, 72 );
//     indexBuffer.emplace_back( 133, 71, 72 );
//     indexBuffer.emplace_back( 68, 134, 133 );
//     indexBuffer.emplace_back( 134, 135, 133 );
//     indexBuffer.emplace_back( 133, 135, 71 );
//     indexBuffer.emplace_back( 135, 70, 71 );
//     indexBuffer.emplace_back( 69, 42, 134 );
//     indexBuffer.emplace_back( 42, 41, 134 );
//     indexBuffer.emplace_back( 134, 41, 135 );
//     indexBuffer.emplace_back( 41, 40, 135 );
//     indexBuffer.emplace_back( 135, 40, 70 );
//     indexBuffer.emplace_back( 40, 5, 70 );
//     indexBuffer.emplace_back( 61, 66, 9 );
//     indexBuffer.emplace_back( 62, 136, 61 );
//     indexBuffer.emplace_back( 63, 137, 62 );
//     indexBuffer.emplace_back( 61, 136, 66 );
//     indexBuffer.emplace_back( 136, 65, 66 );
//     indexBuffer.emplace_back( 62, 137, 136 );
//     indexBuffer.emplace_back( 137, 138, 136 );
//     indexBuffer.emplace_back( 136, 138, 65 );
//     indexBuffer.emplace_back( 138, 64, 65 );
//     indexBuffer.emplace_back( 63, 39, 137 );
//     indexBuffer.emplace_back( 39, 38, 137 );
//     indexBuffer.emplace_back( 137, 38, 138 );
//     indexBuffer.emplace_back( 38, 37, 138 );
//     indexBuffer.emplace_back( 138, 37, 64 );
//     indexBuffer.emplace_back( 37, 4, 64 );
//     indexBuffer.emplace_back( 55, 60, 8 );
//     indexBuffer.emplace_back( 56, 139, 55 );
//     indexBuffer.emplace_back( 57, 140, 56 );
//     indexBuffer.emplace_back( 55, 139, 60 );
//     indexBuffer.emplace_back( 139, 59, 60 );
//     indexBuffer.emplace_back( 56, 140, 139 );
//     indexBuffer.emplace_back( 140, 141, 139 );
//     indexBuffer.emplace_back( 139, 141, 59 );
//     indexBuffer.emplace_back( 141, 58, 59 );
//     indexBuffer.emplace_back( 57, 33, 140 );
//     indexBuffer.emplace_back( 33, 32, 140 );
//     indexBuffer.emplace_back( 140, 32, 141 );
//     indexBuffer.emplace_back( 32, 31, 141 );
//     indexBuffer.emplace_back( 141, 31, 58 );
//     indexBuffer.emplace_back( 31, 3, 58 );
//     indexBuffer.emplace_back( 49, 54, 7 );
//     indexBuffer.emplace_back( 50, 142, 49 );
//     indexBuffer.emplace_back( 51, 143, 50 );
//     indexBuffer.emplace_back( 49, 142, 54 );
//     indexBuffer.emplace_back( 142, 53, 54 );
//     indexBuffer.emplace_back( 50, 143, 142 );
//     indexBuffer.emplace_back( 143, 144, 142 );
//     indexBuffer.emplace_back( 142, 144, 53 );
//     indexBuffer.emplace_back( 144, 52, 53 );
//     indexBuffer.emplace_back( 51, 21, 143 );
//     indexBuffer.emplace_back( 21, 20, 143 );
//     indexBuffer.emplace_back( 143, 20, 144 );
//     indexBuffer.emplace_back( 20, 19, 144 );
//     indexBuffer.emplace_back( 144, 19, 52 );
//     indexBuffer.emplace_back( 19, 2, 52 );
//     indexBuffer.emplace_back( 43, 48, 11 );
//     indexBuffer.emplace_back( 44, 145, 43 );
//     indexBuffer.emplace_back( 45, 146, 44 );
//     indexBuffer.emplace_back( 43, 145, 48 );
//     indexBuffer.emplace_back( 145, 47, 48 );
//     indexBuffer.emplace_back( 44, 146, 145 );
//     indexBuffer.emplace_back( 146, 147, 145 );
//     indexBuffer.emplace_back( 145, 147, 47 );
//     indexBuffer.emplace_back( 147, 46, 47 );
//     indexBuffer.emplace_back( 45, 24, 146 );
//     indexBuffer.emplace_back( 24, 23, 146 );
//     indexBuffer.emplace_back( 146, 23, 147 );
//     indexBuffer.emplace_back( 23, 22, 147 );
//     indexBuffer.emplace_back( 147, 22, 46 );
//     indexBuffer.emplace_back( 22, 6, 46 );
//     indexBuffer.emplace_back( 27, 42, 6 );
//     indexBuffer.emplace_back( 26, 148, 27 );
//     indexBuffer.emplace_back( 25, 149, 26 );
//     indexBuffer.emplace_back( 27, 148, 42 );
//     indexBuffer.emplace_back( 148, 41, 42 );
//     indexBuffer.emplace_back( 26, 149, 148 );
//     indexBuffer.emplace_back( 149, 150, 148 );
//     indexBuffer.emplace_back( 148, 150, 41 );
//     indexBuffer.emplace_back( 150, 40, 41 );
//     indexBuffer.emplace_back( 25, 36, 149 );
//     indexBuffer.emplace_back( 36, 35, 149 );
//     indexBuffer.emplace_back( 149, 35, 150 );
//     indexBuffer.emplace_back( 35, 34, 150 );
//     indexBuffer.emplace_back( 150, 34, 40 );
//     indexBuffer.emplace_back( 34, 5, 40 );
//     indexBuffer.emplace_back( 34, 39, 5 );
//     indexBuffer.emplace_back( 35, 151, 34 );
//     indexBuffer.emplace_back( 36, 152, 35 );
//     indexBuffer.emplace_back( 34, 151, 39 );
//     indexBuffer.emplace_back( 151, 38, 39 );
//     indexBuffer.emplace_back( 35, 152, 151 );
//     indexBuffer.emplace_back( 152, 153, 151 );
//     indexBuffer.emplace_back( 151, 153, 38 );
//     indexBuffer.emplace_back( 153, 37, 38 );
//     indexBuffer.emplace_back( 36, 30, 152 );
//     indexBuffer.emplace_back( 30, 29, 152 );
//     indexBuffer.emplace_back( 152, 29, 153 );
//     indexBuffer.emplace_back( 29, 28, 153 );
//     indexBuffer.emplace_back( 153, 28, 37 );
//     indexBuffer.emplace_back( 28, 4, 37 );
//     indexBuffer.emplace_back( 28, 33, 4 );
//     indexBuffer.emplace_back( 29, 154, 28 );
//     indexBuffer.emplace_back( 30, 155, 29 );
//     indexBuffer.emplace_back( 28, 154, 33 );
//     indexBuffer.emplace_back( 154, 32, 33 );
//     indexBuffer.emplace_back( 29, 155, 154 );
//     indexBuffer.emplace_back( 155, 156, 154 );
//     indexBuffer.emplace_back( 154, 156, 32 );
//     indexBuffer.emplace_back( 156, 31, 32 );
//     indexBuffer.emplace_back( 30, 15, 155 );
//     indexBuffer.emplace_back( 15, 14, 155 );
//     indexBuffer.emplace_back( 155, 14, 156 );
//     indexBuffer.emplace_back( 14, 13, 156 );
//     indexBuffer.emplace_back( 156, 13, 31 );
//     indexBuffer.emplace_back( 13, 3, 31 );
//     indexBuffer.emplace_back( 22, 27, 6 );
//     indexBuffer.emplace_back( 23, 157, 22 );
//     indexBuffer.emplace_back( 24, 158, 23 );
//     indexBuffer.emplace_back( 22, 157, 27 );
//     indexBuffer.emplace_back( 157, 26, 27 );
//     indexBuffer.emplace_back( 23, 158, 157 );
//     indexBuffer.emplace_back( 158, 159, 157 );
//     indexBuffer.emplace_back( 157, 159, 26 );
//     indexBuffer.emplace_back( 159, 25, 26 );
//     indexBuffer.emplace_back( 24, 18, 158 );
//     indexBuffer.emplace_back( 18, 17, 158 );
//     indexBuffer.emplace_back( 158, 17, 159 );
//     indexBuffer.emplace_back( 17, 16, 159 );
//     indexBuffer.emplace_back( 159, 16, 25 );
//     indexBuffer.emplace_back( 16, 1, 25 );
//     indexBuffer.emplace_back( 13, 21, 3 );
//     indexBuffer.emplace_back( 14, 160, 13 );
//     indexBuffer.emplace_back( 15, 161, 14 );
//     indexBuffer.emplace_back( 13, 160, 21 );
//     indexBuffer.emplace_back( 160, 20, 21 );
//     indexBuffer.emplace_back( 14, 161, 160 );
//     indexBuffer.emplace_back( 161, 162, 160 );
//     indexBuffer.emplace_back( 160, 162, 20 );
//     indexBuffer.emplace_back( 162, 19, 20 );
//     indexBuffer.emplace_back( 15, 16, 161 );
//     indexBuffer.emplace_back( 16, 17, 161 );
//     indexBuffer.emplace_back( 161, 17, 162 );
//     indexBuffer.emplace_back( 17, 18, 162 );
//     indexBuffer.emplace_back( 162, 18, 19 );
//     indexBuffer.emplace_back( 18, 2, 19 );

//     for (int i = 0; i < normals.size(); i++)
//         vertexBuffer.emplace_back(vertices[i], colours[i], normals[i]);

//     std::cout << "tirangles: " << indexBuffer.size() << '\n';

//     for (Vector& i : indexBuffer)
//         i = i + Vector(-1, -1, -1);

//     return new Mesh(indexBuffer, vertexBuffer);
// }
