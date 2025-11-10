#pragma once

#include "Bitmap3D.hpp"
#include "Window.hpp"
#include "scene/Scene.hpp"
#include <memory>

class Renderer {
private:
    int width, height;

    Window window = Window(width, height);
    Bitmap3D bitmap = Bitmap3D(width, height);
    std::shared_ptr<Scene> scene;

public:
    //constructors/destructor
    Renderer(int width, int height, std::shared_ptr<Scene> s);

    //public methods
    void drawCall();
};