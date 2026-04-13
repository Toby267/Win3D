#pragma once

#include "engine/Engine.hpp"

/**
 * Abstract class that each application inherits from
 */
class Application {
public:
    //constructors/destructor
    virtual void runApp(Engine e) = 0;
};

// bunny scene with 1440 triangles, at 400x400 resolution
class bunny1440_400 : public Application {
public:
    void runApp(Engine e) override;
};