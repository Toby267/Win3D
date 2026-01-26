#pragma once

#include "scene/dataStructures/Aabb.hpp"
#include "util/Util.hpp"

#include <vector>

struct Vertex {
    Vector position;
    Colour colour;
    Vector normal;
} typedef Vertex;

struct Triangle {
    Vertex v1;
    Vertex v2;
    Vertex v3;

    Aabb calcBBox() const;
} typedef Triangle;

typedef std::vector<Vector> IndexBuffer;
typedef std::vector<Vertex> VertexBuffer;