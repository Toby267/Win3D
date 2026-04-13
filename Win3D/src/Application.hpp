#pragma once

//Class representing the application that I will use to test the renderer. This is what the driver will call, and the main loop is within this class
#include "engine/Engine.hpp"

class Application {
public:
    //constructors/destructor
    Application(Engine& e);
};