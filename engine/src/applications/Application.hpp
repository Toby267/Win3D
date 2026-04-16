#pragma once

#include "engine/Engine.hpp"

/**
 * Namesapce representing each application, that can be called from main
 */
namespace Apps {
    void speedTestApp(int width, int height, RenderType type, std::string meshPath);
    void bunnyApp(RenderType type);
    void triangleApp(RenderType type);
    void objectsApp(RenderType type);
}
