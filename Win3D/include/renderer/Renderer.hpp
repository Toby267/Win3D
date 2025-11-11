#pragma once

#include "Bitmap3D.hpp"
#include "Window.hpp"
#include "Viewport.hpp"
#include "scene/Scene.hpp"
#include <memory>

class Renderer {
private:
    int width, height, depthOfField, FieldOfView;

    Window window = Window(width, height);
    Bitmap3D bitmap = Bitmap3D(width, height);
    Viewport viewport = Viewport(width, height, depthOfField);

    std::shared_ptr<Scene> scene;

public:
    //constructors/destructor
    Renderer(int screenWidth, int screenHeight, int depthOfField, int FieldOfView, std::shared_ptr<Scene> s);

    //public methods
    void drawCall();
};