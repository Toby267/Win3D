#pragma once

#include "engine/Bitmap3D.hpp"
#include "scene/core/Scene.hpp"

namespace Renderer {
    void rasterize(Bitmap3D& bmap, const Scene& scene);
    void rayTrace(Bitmap3D& bmap, const Scene& scene);
};
