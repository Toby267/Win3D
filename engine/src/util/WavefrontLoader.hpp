#pragma once

#include "engine/Bitmap3D.hpp"
#include "scene/objects/Mesh.hpp"
#include "util/Util.hpp"

/**
 * Namespace for all file handling functions
 */
namespace files {
    Mesh* loadWavefront(std::string path, Colour colour);
    void saveAsPPM(const Bitmap3D& bmap, std::string path);
}
