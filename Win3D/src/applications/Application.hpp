#pragma once

//Class representing the application that I will use to test the renderer. This is what the driver will call, and the main loop is within this class
#include "engine/Engine.hpp"

class Application {
public:
    //constructors/destructor
    virtual void runApp(Engine e) = 0;
};

class bunny1440_400 : public Application {
public:
    void runApp(Engine e) override;
};