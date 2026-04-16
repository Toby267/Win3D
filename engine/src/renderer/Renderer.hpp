#pragma once

#include "engine/Bitmap3D.hpp"
#include "scene/core/Scene.hpp"

/*
object space is defined as:
    range: (-100, -100, -100) to (100, 100, 100)
    directions: +x=right, +y=up, +z=into the screen
world space is defined as:
    range: infinite
    directions: doesn't apply, the camera can be anywhere pointing anywhere, but if we're talking about a scene as a whole: +x=right, +y=up, +z=into the screen
camera space is defined as:
    range: infinite
    directions:+x=right, +y=up, +z=into the screen
clip space/ndc:
    range: (-1, -1, -1), to (1, 1, 1)
    directions: +x=right, +y=up, +z=into the screen
viewport space:
    range: (0, 0, 0) to (width, height, 10000)
    directions:+x=right, +y=down, +z=into the screen
*/

/**
 * Namespace for all rendering pipelines
 */
namespace Renderer {
    void rasterize(Bitmap3D& bmap, const Scene& scene);
    void rayTrace(Bitmap3D& bmap, const Scene& scene);
};
