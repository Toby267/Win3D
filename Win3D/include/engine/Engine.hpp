#pragma once

#include "engine/Bitmap3D.hpp"
#include "engine/Window.hpp"
#include "renderer/CameraRayTracer.hpp"
#include "renderer/CameraRasterizer.hpp"

class Engine {
private:
    // scene (in terms of objects and lights and the such)
    // cameras (one for raster, one for ray tracing, etc)
    // window

    const int WIDTH = 1280;
    const int HEIGHT = 720;

    CameraRasterizer cameraRaster = CameraRasterizer();
    CameraRayTracer cameraRayTracer = CameraRayTracer();
    Window window = Window(WIDTH, HEIGHT);

    Bitmap3D bitmap = Bitmap3D(WIDTH, HEIGHT);

public:
    void drawCall(std::vector<Mesh> objects);

private:

};