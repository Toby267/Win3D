#include "applications/Application.hpp"
#include "engine/Engine.hpp"
#include <cassert>
#include <iostream>
#include <string>

/*
scenes:
- bunny
- triangle
- objects
*/

//Driver code; inputs are of the form <./bin/Win3D meshPath width height renderType> or <./bin/Win3D scene renderType> or <./bin/Win3D>
int main(int argc, char *argv[]) {
    if (argc == 1) {
        // default scene
        Apps::bunnyApp(RAY_TRACER);
    }
    else if (argc == 3) {
        // one of the hardcoded scenes
        std::string scene = argv[1];
        RenderType type = ((std::string)argv[2] == "-t") ? RenderType::RAY_TRACER : RenderType::RASTERIZER;
        if (scene == "bunny") {
            Apps::bunnyApp(type);
        }
        else if (scene == "triangle") {
            Apps::triangleApp(type);
        }
        else if (scene == "objects") {
            Apps::objectsApp(type);
        }
    }
    else if (argc == 5) {
        // specific custome scene
        std::string mesh = argv[1];
        int width = std::stoi(argv[2]);
        int height = std::stoi(argv[3]);
        RenderType type = ((std::string)argv[4] == "-t") ? RenderType::RAY_TRACER : RenderType::RASTERIZER;
        
        Apps::speedTestApp(width, height, type, mesh);
    }
    else {
        std::cerr << "Invalid number of arguments" << '\n';
    }

    return 0;
}
