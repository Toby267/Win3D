#include "Application.hpp"
#include "engine/Engine.hpp"
#include <cassert>
#include <iostream>

/*
scenes:
- bunny1440_400
*/

//Driver code
int main(int argc, char *argv[]) {
    assert(argc == 1 || argc == 2);
    
    // default scene
    if (argc == 1) {
        Engine e = Engine(400, 400);
        Application app = Application(e);

        return 0;
    }

    // other scenes
    std::string scene = argv[1];
    if (scene == "bunny1440_400") {
        Engine e = Engine(400, 400);
        Application app = Application(e);
    }
    else {
        std::cerr << "Invalid scene ID" << '\n';
    }

    return 0;
}
