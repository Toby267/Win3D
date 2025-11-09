#pragma once

#include "Bitmap3D.hpp"
#include "Window.hpp"
#include "scene/Scene.hpp"

class Renderer {
private:
    int width, height;

    Window window = Window(width, height);
    Bitmap3D bitmap = Bitmap3D(width, height);
    Scene scene = Scene();

public:
    //constructors/destructor
    Renderer(int width, int height);

private:
    //private methods
    void drawCall();
};