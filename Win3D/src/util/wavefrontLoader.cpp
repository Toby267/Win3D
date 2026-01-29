#include "util/WavefrontLoader.hpp"
#include "scene/core/SceneUtil.hpp"
#include "scene/objects/Mesh.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

// assumes path to start from ./resources
Mesh* Wavefront::loadWavefront(std::string path) {
    IndexBuffer indexBuffer{};
    VertexBuffer vertexBuffer{};

    std::ifstream obj(RESOURCES_PATH + path);
    assert(obj);

    std::string s;
    while (std::getline(obj, s))
        std::cout << s << '\n';

    obj.close();

    return new Mesh(indexBuffer, vertexBuffer);
}