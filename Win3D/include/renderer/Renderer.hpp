#pragma once

#include "Bitmap3D.hpp"
#include "Window.hpp"
#include "graphicsPipelineOop/GraphicsPipelineClass.hpp"
#include <vector>

class Renderer {
private:
    Window window;
    Bitmap3D bitmap;

    GraphicsPipelineClass pipeline{};

public:
    //constructors/destructor
    Renderer(int screenWidth, int screenHeight);

    //public methods
    void drawCall(std::vector<Object3D> objects);
};