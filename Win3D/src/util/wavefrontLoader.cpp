#include "util/WavefrontLoader.hpp"
#include "scene/core/SceneUtil.hpp"
#include "scene/dataStructures/Aabb.hpp"
#include <vector>

Mesh* Wavefront::loadWavefront(std::string path) {
    IndexBuffer indexBuffer{};
    VertexBuffer vertexBuffer{};
    
    std::vector<Triangle> triangles{};
    std::vector<Triangle> normaLS{};
}