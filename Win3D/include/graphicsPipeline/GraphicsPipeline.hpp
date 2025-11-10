#pragma once

#include "scene/Scene.hpp"
#include "renderer/Bitmap3D.hpp"

namespace GraphicsPipeline {
    void DrawCall(const Scene& scene, Bitmap3D& bitmap);
}