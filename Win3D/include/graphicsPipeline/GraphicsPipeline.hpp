#pragma once

#include "scene/Scene.hpp"
#include "renderer/Bitmap3D.hpp"
#include "renderer/Viewport.hpp"

namespace GraphicsPipeline {
    void DrawCall(const Scene& scene, Bitmap3D& bitmap, const Viewport& viewport);
}