#pragma once

#include "util/Util.hpp"

#include <cstddef>
#include <vector>

// represents a single vertex
struct Vertex {
    Vector position;
    Colour colour;
    Vector normal;
    double u;
    double v;
} typedef Vertex;

// represents the indeces into the vertex array for a triangle
struct Index {
    size_t position;
    size_t colour;
    size_t uv;
    size_t normal;
} typedef Index;

// definitions for the index buffer and vertex buffer
typedef std::vector<Index> IndexBuffer;
typedef std::vector<Vertex> VertexBuffer;
