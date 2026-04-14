#pragma once

#include "engine/Engine.hpp"

class speedTestApp {
public:
    void runApp(int width, int height, RenderType type, std::string meshPath);
};

class bunnySceneApp {
public:
    void runApp(RenderType type);
};