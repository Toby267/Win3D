#pragma once

#include "Bitmap3D.hpp"
#include "Window.hpp"
#include "scene/Scene.hpp"

class Renderer {
private:
    int width, height;

    Window window;
    Bitmap3D bitmap;
    Scene scene;

public:
    //constructors/destructor
    Renderer(int width, int height);

private:
    //private methods
    void drawCall();
};