#include "util/Files.hpp"
#include "scene/core/SceneUtil.hpp"
#include "scene/objects/Mesh.hpp"
#include "util/Util.hpp"
#include <cassert>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// stores the current contents of the bitmap as a ppm file at the specified file locaiton. Does not create directories for the path
void Files::writePPM(const Bitmap3D& bmap, std::string path) {
    // open file
    std::ofstream f(RESOURCES_PATH + path, std::ios::binary);
    assert(f);

    int width = bmap.getWidth(), height = bmap.getHeight();
    const std::vector<unsigned char>& frameBuffer = bmap.getFrameBuffer();

    f << "P6\n";                            // format
    f << width << ' ' << height << '\n';    // width and height
    f << "255\n";                           // max colour value

    // write data
    for (int i = 0; i < width*height; i++) {
        const char rgb[3] = {
            (char)frameBuffer[4*i + 0],
            (char)frameBuffer[4*i + 1],
            (char)frameBuffer[4*i + 2]
        };
        f.write(rgb, 3);
    }

    // close
    f.close();
}

// reads a .obj file including its positions, normals and uv coordinates. assumes path to start from ./resources
Mesh* Files::readWavefront(std::string path, Colour colour) {
    IndexBuffer indexBuffer{};
    VertexBuffer vertexBuffer;

    std::vector<Vector> positions{};
    std::vector<Vector> normals{};
    std::vector<double> us, vs;

    std::ifstream obj(RESOURCES_PATH + path);
    assert(obj);

    std::string s;
    
    // for each line in the .obj file
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
            // parsing indeces
            for (int i = 0; i < 3; i++) {
                std::string term;
                line >> term;

                size_t index1 = term.find("/");
                size_t index2 = term.find("/", index1+1);

                std::string v  = term.substr(0, index1);
                std::string vt = term.substr(index1+1, index2-index1-1);
                std::string vn = term.substr(index2+1);

                indexBuffer.emplace_back(Index{(size_t)std::stoi(v) - 1, 0, (size_t)std::stoi(vt) - 1, (size_t)std::stoi(vn) - 1});
            }
        }
        else if (word == "vt") {
            // parsing UVs
            us.emplace_back(0);
            line >> us.back();

            vs.emplace_back(0);
            line >> vs.back();
        }
    }

    // convert data to index and vertex buffers
    vertexBuffer.reserve(us.size());

    for (int i = 0; i < normals.size(); i++)
        vertexBuffer.emplace_back(positions[i], colour, normals[i], us[i], vs[i]);
    for (int i = normals.size(); i < us.size(); i++)
        vertexBuffer.emplace_back(Vector{-1, -1, -1, -1}, Colour{-1, -1, -1, -1}, Vector{-1, -1, -1}, us[i], vs[i]);

    // close file
    obj.close();

    // return
    return new Mesh(indexBuffer, vertexBuffer);
}
