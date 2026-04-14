#pragma once

#include "engine/Engine.hpp"

// a function for each separate app that uses the renderer
namespace Apps {
    void speedTestApp(int width, int height, RenderType type, std::string meshPath);
    void bunnyApp(RenderType type);
    void triangleApp(RenderType type);
    void objectsApp(RenderType type);
}
