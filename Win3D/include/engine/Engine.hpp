#pragma once

#include "engine/Bitmap3D.hpp"
#include "engine/Window.hpp"
#include "renderer/RayTracer.hpp"
#include "renderer/Rasterizer.hpp"
#include "scene/Scene.hpp"

class Engine {
private:
    // scene (in terms of objects and lights and the such)
    // cameras (one for raster, one for ray tracing, etc)
    // window

    const int WIDTH = 640;
    const int HEIGHT = 480;

    Scene scene{WIDTH, HEIGHT};

    Rasterizer cameraRaster{scene};
    RayTracer cameraRayTracer{scene};

    Window window{WIDTH, HEIGHT};

    Bitmap3D bitmap{WIDTH, HEIGHT};

public:
    void drawCall();
    
    Scene& getScene();
};