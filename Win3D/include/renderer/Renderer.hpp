#pragma once

#include <vector>

#include "scene/Camera.hpp"
#include "Bitmap3D.hpp"
#include "Window.hpp"
#include "graphicsPipeline/Rasterizer.hpp"
#include "graphicsPipeline/RayTracer.hpp"

/*
The rendering engine, consisting of the window to be drawn to, the bitmap to store a frame, and the pipeline to process scenes
*/
class Renderer {
private:
    double width;
    double height;

    Window window;
    Bitmap3D bitmap;

    Camera camera;
    Viewport viewport;

    Rasterizer rasterizer;

    RayTracer tracer;

public:
    //constructors/destructor
    Renderer(int screenWidth, int screenHeight);

    //public methods
    void drawCall(std::vector<Object3D> objects);

private:
    //private methods
    void drawCallRaster(std::vector<Object3D> objects);
    void drawCallRayTraced(std::vector<Object3D> objects);

    //geometry processing functions
    void processGeometry(std::vector<Object3D>& objects);
    void processGeometryRayTracing(std::vector<Object3D>& objects);
};