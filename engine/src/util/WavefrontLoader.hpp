#pragma once

#include "scene/objects/Mesh.hpp"
#include "util/Util.hpp"

/**
 * Namespace for all wavefront/.obj file handling functions
 */
namespace Wavefront {
    Mesh* loadWavefront(std::string path, Colour colour);
}
