#include "applications/Application.hpp"
#include "engine/Engine.hpp"
#include <cassert>
#include <iostream>

/*
scenes:
- bunny1440_400_trace
*/

/*
features:
- dynamic scenes
- raster renderer /w triangle colour interpolation
- ray casting renderer /w shading from the rendering equation
- bvh optimisation
- bxdf material system
- reinhard tone mapping
- exposure scaling
- mutliple light source functionality
- disney bsdf
*/

//Driver code
int main(int argc, char *argv[]) {
    assert(argc == 1 || argc == 2);
    
    // default scene
    if (argc == 1) {
        bunny1440_400 app{};
        app.runApp(Engine(400, 400, RASTERIZER));

        return 0;
    }

    // other scenes
    std::string scene = argv[1];
    if (scene == "bunny1440_400_trace") {
        bunny1440_400 app{};
        app.runApp(Engine(400, 400, RAY_TRACER));
    }
    else {
        std::cerr << "Invalid scene ID" << '\n';
    }

    return 0;
}
