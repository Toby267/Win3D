#include "Application.hpp"

#include "engine/Engine.hpp"
#include <numbers>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Runs the application
 */
Application::Application() {
    Engine e{};
    Scene& scene = e.getScene();

    Mesh* cube1 = scene.addObject(Mesh::cube(Colour::blue()));
    cube1->setTranslation(Matrix::translate(-800, 0, 1100));

    Mesh* cube2 = scene.addObject(Mesh::cube(Colour::blue()));
    cube2->setTranslation(Matrix::translate(-400, 0, 1100));

    Mesh* cube3 = scene.addObject(Mesh::cube(Colour::blue()));
    cube3->setTranslation(Matrix::translate(400, 0, 1100));

    Mesh* cube4 = scene.addObject(Mesh::cube(Colour::blue()));
    cube4->setTranslation(Matrix::translate(800, 0, 1100));

    Mesh* sphere = scene.addObject(Mesh::icoSphere(Colour::blue()));
    sphere->setTranslation(Matrix::translate(0, 0, 1000));

    double alpha = 0.0;

    for (;;) {
        alpha -= std::numbers::pi/16;
        cube1->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        cube2->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        cube3->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        cube4->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        sphere->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        
        e.drawCall();
    }
}
