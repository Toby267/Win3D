#pragma once

#include <vector>

#include "Bitmap3D.hpp"
#include "Window.hpp"
#include "graphicsPipeline/GeometryProcessor.hpp"
#include "graphicsPipeline/Rasterizer.hpp"

/*
The rendering engine, consisting of the window to be drawn to, the bitmap to store a frame, and the pipeline to process scenes
*/
class Renderer {
private:
    double width;
    double height;

    Window window;
    Bitmap3D bitmap;

    // GraphicsPipeline pipeline;
    GeometryProcessor geometryProcessor;
    Rasterizer rasterizer;

public:
    //constructors/destructor
    Renderer(int screenWidth, int screenHeight);

    //public methods
    void drawCall(std::vector<Object3D> objects);

private:
    //private methods
    void drawCallRaster(std::vector<Object3D> objects);
    void drawCallRayTraced(std::vector<Object3D> objects);
};