#pragma once

#include "renderer/Bitmap3D.hpp"
#include "renderer/Window.hpp"
#include "scene/CameraRayTracer.hpp"
#include "scene/Scene.hpp"
#include "scene/CameraRasterizer.hpp"

class Engine {
private:
    // scene (in terms of objects and lights and the such)
    // cameras (one for raster, one for ray tracing, etc)
    // window

    const int WIDTH = 1280;
    const int HEIGHT = 720;

    Scene scene = Scene();
    CameraRasterizer cameraRaster = CameraRasterizer();
    Camera cameraRayTracer = Camera();
    Window window = Window(WIDTH, HEIGHT);

    Bitmap3D bitmap = Bitmap3D(WIDTH, HEIGHT);


public:
    void drawCall(std::vector<Object> objects);

private:

};