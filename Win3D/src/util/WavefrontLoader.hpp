#pragma once

#include "scene/objects/Mesh.hpp"
#include "util/Util.hpp"

namespace Wavefront {
    Mesh* loadWavefront(std::string path, Colour colour);
}