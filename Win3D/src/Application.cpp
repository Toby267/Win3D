#include "Application.hpp"

#include "engine/Engine.hpp"
#include <iostream>
#include <numbers>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Runs the application
 */
Application::Application() {
    Engine* e = new Engine();
    Scene& scene = e->getScene();

    Mesh* cube1 = scene.addObject(Mesh::cube(Colour::blue()));
    cube1->setScale(Matrix::scale(100, 100, 100));
    cube1->setTranslation(Matrix::translate(-300, 0, 1100));
    cube1->setRotation(Matrix::rotation(0, 0, 0));

    Mesh* sphere = scene.addObject(Mesh::icoSphere(Colour::blue()));
    sphere->setScale(Matrix::scale(100, 100, 100));
    sphere->setTranslation(Matrix::translate(300, 0, 1000));
    sphere->setRotation(Matrix::rotation(0, 0, 0));

    double alpha = 0.0;

    for (;;) {
        alpha -= std::numbers::pi/16;
        cube1->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        
        e->drawCall();
        // std::cin.get();
    }

    delete e;
}
