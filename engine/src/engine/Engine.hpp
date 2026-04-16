#pragma once

#include "engine/Bitmap3D.hpp"
#include "engine/Window.hpp"
#include "scene/core/Scene.hpp"

// represents either the rasterization pipeline or ray tracing pipeline
enum RenderType {
    RASTERIZER,
    RAY_TRACER
};

/**
 * Class representing the engine, that is used for rendering
 *
 * Each engine has its own window, scene, and bitmap, and uses either rasterization or ray tracing
 */
class Engine {
private:
    Scene scene;
    Window window;
    Bitmap3D bitmap;

    RenderType renderType;   

    int framesRendered = 0;

public:
    // constructors/destructor
    Engine(int width, int height, RenderType renderType);

    // getters/setters
    Scene& getScene() { return scene; };

    // public methods
    void drawCall();
    void closeWindow();
};
