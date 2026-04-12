// #include "util/WavefrontLoader.hpp"
// #include "scene/core/SceneUtil.hpp"
// #include "scene/objects/Mesh.hpp"
// #include "util/Util.hpp"
// #include <cassert>
// #include <cstddef>
// #include <fstream>
// #include <iostream>
// #include <sstream>
// #include <string>
// #include <vector>

// //meshes should contain their colour in its material
// //this should also work for faces which aren't just 1//1, 2//2, 4//4, etc

// // assumes path to start from ./resources
// Mesh* Wavefront::loadWavefront(std::string path) {
//     IndexBuffer indexBuffer{};
//     VertexBuffer vertexBuffer;

//     std::vector<Vector> positions{};
//     std::vector<Vector> normals{};
//     std::vector<double> us, vs;

//     std::ifstream obj(RESOURCES_PATH + path);
//     assert(obj);

//     std::string s;
    
//     while (std::getline(obj, s)) {
//         std::stringstream line{s};
//         std::string word;

//         line >> word;

//         if (word == "v") {
//             // parsing a vertex position
//             positions.emplace_back(Vector(4));
//             line >> positions.back().x();
//             line >> positions.back().y();
//             line >> positions.back().z();
//             positions.back().w() = 1;
//         }
//         else if (word == "vn") {
//             // parsing a vertex normal
//             normals.emplace_back(Vector(3));
//             line >> normals.back().x();
//             line >> normals.back().y();
//             line >> normals.back().z();
//         }
//         else if (word == "f") {
//             // parsing a triangle
//             // int v{}, vt{}, vn{};
//             std::cout << "face\n";
//             size_t indeces[3];
//             for (int i = 0; i < 3; i++) {
//                 line >> word;

//                 size_t index = word.find('/');
//                 std::string v = (index == std::string::npos) ? word : word.substr(0, index);
//                 indeces[i] = (size_t)(std::stoi(v) - 1);
//                 // indexBuffer.back()
//                 // indexBuffer.emplace_back(std::stoi(v) - 1);
//             }
//             indexBuffer.emplace_back(Index{indeces[0], indeces[1], 1, indeces[2]});


//             // line >> word;
//             // word = word.substr(0, 1);
//             // indexBuffer.emplace_back(std::stoi(word));

//             // line >> word;
//             // word = word.substr(0, 1);
//             // indexBuffer.emplace_back(std::stoi(word));

//             // line >> word;
//             // word = word.substr(0, 1);
//             // indexBuffer.emplace_back(std::stoi(word));
//         }
//         else if (word == "vt") {
//             // parsing uvs
//             us.emplace_back(0); vs.emplace_back(0);
//             line >> us.back();  line >> vs.back();
//         }
//     }

//     vertexBuffer.reserve(positions.size());
//     // for (int i = 0; i < normals.size(); i++)
//         // vertexBuffer.emplace_back(positions[i], Colour::blue(), normals[i]);

//     for (int i = 0; i < normals.size(); i++)
//         vertexBuffer.emplace_back(positions[i], Colour::blue(), normals[i], us[i], vs[i]);
//     for (int i = normals.size(); i < us.size(); i++)
//         vertexBuffer.emplace_back(Vector{-1, -1, -1, -1}, Colour{-1, -1, -1, -1}, Vector{-1, -1, -1}, us[i], vs[i]);

//     // for (Index& i : indexBuffer) {
//     //     i.colour--;
//     //     i.normal--;
//     //     i.position--;
//     //     i.uv--;
//     // }

//     // for (auto& p : positions)
//     //     std::cout << p << '\n';
//     // for (auto& p : normals)
//     //     std::cout << p << '\n';
//     // for (auto& p : indexBuffer)
//     //     std::cout << p << '\n';

//     obj.close();

//     return new Mesh(indexBuffer, vertexBuffer);
// }