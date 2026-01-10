#pragma once

#include "engine/Bitmap3D.hpp"
#include "engine/Window.hpp"
#include "renderer/RayTracer.hpp"
#include "renderer/Rasterizer.hpp"
#include "scene/Scene.hpp"

class Engine {
private:
    const int WIDTH = 1280;
    const int HEIGHT = 720;

    Scene scene{WIDTH, HEIGHT};

    Rasterizer cameraRaster{scene};
    RayTracer cameraRayTracer{scene};

    Window window{WIDTH, HEIGHT};

    Bitmap3D bitmap{WIDTH, HEIGHT};

public:
    //getters/setters
    Scene& getScene() { return scene; };

    //public methods
    void drawCall();
};