#pragma once

#include "util/Util.hpp"

#include <vector>

struct Vertex {
    Vector position;
    Colour colour;
    Vector normal;
} typedef Vertex;

typedef std::vector<Vector> IndexBuffer;
typedef std::vector<Vertex> VertexBuffer;