#include "applications/Application.hpp"
#include "engine/Engine.hpp"
#include <cassert>
#include <iostream>
#include <string>

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

//Driver code; inputs are of the form <./bin/Win3D meshPath width height renderType> or <./bin/Win3D scene renderType> or <./bin/Win3D>
int main(int argc, char *argv[]) {
    if (argc == 1) {
        // default scene
        bunnySceneApp app{};
        app.runApp(RAY_TRACER);

        return 0;
    }
    else if (argc == 3) {
        // one of the hardcoded scenes
        std::string scene = argv[1];
        RenderType type = ((std::string)argv[2] == "tracer") ? RenderType::RAY_TRACER : RenderType::RASTERIZER;
        if (scene == "bunny") {
            bunnySceneApp app{};
            app.runApp(RAY_TRACER);
        }
    }
    else if (argc == 5) {
        // specific custome scene
        std::string mesh = argv[1];
        int width = std::stoi(argv[2]);
        int height = std::stoi(argv[3]);
        RenderType type = ((std::string)argv[4] == "tracer") ? RenderType::RAY_TRACER : RenderType::RASTERIZER;
        
        speedTestApp app{};
        app.runApp(width, height, type, mesh);
    }
    else {
        std::cerr << "Invalid number of arguments" << '\n';
    }

    return 0;
}
