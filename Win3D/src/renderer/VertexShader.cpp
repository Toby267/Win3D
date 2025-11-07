#include "renderer/VertexShader.hpp"

void VertexShader::draw(const Scene& scene, Bitmap3D& bitmap) {
    bitmap.drawTriangle(Vector(0, 720-1, 0), Vector(1280/2.0, 0, 0), Vector(1280-1, 720-1, 0), Colour(255, 0, 0), Colour(0, 255, 0), Colour(0, 0, 255));
}