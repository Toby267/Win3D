#include "util/WavefrontLoader.hpp"
#include "scene/core/SceneUtil.hpp"
#include "scene/objects/Mesh.hpp"
#include "util/Util.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//meshes should contain their colour in its material
//this should also work for faces which aren't just 1//1, 2//2, 4//4, etc

// assumes path to start from ./resources
Mesh* Wavefront::loadWavefront(std::string path) {
    IndexBuffer indexBuffer{};
    VertexBuffer vertexBuffer;

    std::vector<Vector> positions{};
    std::vector<Vector> normals{};

    std::ifstream obj(RESOURCES_PATH + path);
    assert(obj);

    std::string s;
    
    while (std::getline(obj, s)) {
        std::stringstream line{s};
        std::string word;

        line >> word;

        if (word == "v") {
            // parsing a vertex position
            positions.emplace_back(Vector(4));
            line >> positions.back().x();
            line >> positions.back().y();
            line >> positions.back().z();
            positions.back().w() = 1;
        }
        else if (word == "vn") {
            // parsing a vertex normal
            normals.emplace_back(Vector(3));
            line >> normals.back().x();
            line >> normals.back().y();
            line >> normals.back().z();
        }
        else if (word == "f") {
            // parsing a triangle
            line >> word;
            word = word.substr(0, 1);
            indexBuffer.emplace_back(std::stoi(word));

            line >> word;
            word = word.substr(0, 1);
            indexBuffer.emplace_back(std::stoi(word));

            line >> word;
            word = word.substr(0, 1);
            indexBuffer.emplace_back(std::stoi(word));
        }
    }

    vertexBuffer.reserve(positions.size());
    for (int i = 0; i < normals.size(); i++)
        vertexBuffer.emplace_back(positions[i], Colour::blue(), normals[i]);

    for (Index& i : indexBuffer) {
        i.colour--;
        i.normal--;
        i.position--;
        i.uv--;
    }

    // for (auto& p : positions)
    //     std::cout << p << '\n';
    // for (auto& p : normals)
    //     std::cout << p << '\n';
    // for (auto& p : indexBuffer)
    //     std::cout << p << '\n';

    obj.close();

    return new Mesh(indexBuffer, vertexBuffer);
}