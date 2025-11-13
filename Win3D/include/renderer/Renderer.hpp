#pragma once

#include <vector>

#include "Bitmap3D.hpp"
#include "Window.hpp"
#include "graphicsPipeline/GraphicsPipeline.hpp"

/*
The rendering engine, consisting of the window to be drawn to, the bitmap to store a frame, and the pipeline to process scenes
*/
class Renderer {
private:
    Window window;
    Bitmap3D bitmap;

    GraphicsPipeline pipeline{};

public:
    //constructors/destructor
    Renderer(int screenWidth, int screenHeight);

    //public methods
    void drawCall(std::vector<Object3D> objects);
};