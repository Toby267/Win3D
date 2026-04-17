#pragma once

#include "engine/Bitmap3D.hpp"
#include "scene/objects/Mesh.hpp"
#include "util/Util.hpp"

/**
 * Namespace for all file handling functions
 */
namespace Files {
    void writePPM(const Bitmap3D& bmap, std::string path);
    Mesh* readWavefront(std::string path, Colour colour);
}
