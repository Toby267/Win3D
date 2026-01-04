#include "Application.hpp"

#include "engine/Engine.hpp"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Runs the application
 */
Application::Application() {
    Engine* e = new Engine();

    for (;;) {
        e->drawCall();
        std::cin.get();
    }

    delete e;
}
