#pragma once

#include "engine/Bitmap3D.hpp"
#include "engine/Window.hpp"
#include "scene/core/Scene.hpp"

/**
 * Class representing the engine, that is used for rendering.
 *
 * Each engine has its own window and scene.
 */
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