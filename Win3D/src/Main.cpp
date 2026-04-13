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

//Driver code; inputs are of the form <./bin/Win3D meshPath resolution renderType> or <./bin/Win3D scene> or <./bin/Win3D>
int main(int argc, char *argv[]) {
    if (argc == 1) {
        // default scene
        speedTestApp app{};
        app.runApp(400, 400, RAY_TRACER, "bunny_1440");

        return 0;
    }
    else if (argc == 2) {
        // one of the hardcoded scenes
    }
    else if (argc == 4) {
        // specific custome scene
        std::string mesh = argv[1];
        int resolution = std::stoi(argv[2]);
        RenderType type = ((std::string)argv[3] == "tracer") ? RenderType::RAY_TRACER : RenderType::RASTERIZER;
        
        speedTestApp app{};
        app.runApp(resolution, resolution, type, mesh);
    }
    else {
        std::cerr << "Invalid number of arguments" << '\n';
    }

    return 0;
}
