#pragma once

#include "renderer/Window.hpp"
#include "scene/Scene.hpp"
#include "scene/CameraRasterizer.hpp"

class Engine {
private:
    // scene (in terms of objects and lights and the such)
    // cameras (one for raster, one for ray tracing, etc)
    // window

    Scene scene = Scene();
    CameraRasterizer camera = CameraRasterizer();
    Window window = Window(1280, 720);


public:

private:

};