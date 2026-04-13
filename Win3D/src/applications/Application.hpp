#pragma once

#include "engine/Engine.hpp"

/**
 * Abstract class that each application inherits from
 */
class Application {
public:
    //constructors/destructor
    virtual void runApp(int width, int height, RenderType type, std::string meshPath) = 0;
};

// bunny scene with 1440 triangles, at 400x400 resolution
class speedTestApp : public Application {
public:
    void runApp(int width, int height, RenderType type, std::string meshPath) override;
};