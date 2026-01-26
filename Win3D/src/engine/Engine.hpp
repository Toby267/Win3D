#pragma once

#include "engine/Bitmap3D.hpp"
#include "engine/Window.hpp"
#include "scene/Scene.hpp"

class Engine {
private:
    Scene scene;
    Window window;
    Bitmap3D bitmap;

public:
    //constructors/destructor
    Engine(int width, int height);

    //getters/setters
    Scene& getScene() { return scene; };

    //public methods
    void drawCall();
};