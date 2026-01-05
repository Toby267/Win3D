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
    cube1->setTranslation(Matrix::translate(-300, 0, 1100));

    Mesh* sphere = scene.addObject(Mesh::icoSphere(Colour::blue()));
    sphere->setTranslation(Matrix::translate(300, 0, 1000));

    scene.setUpBvh();

    double alpha = 0.0;

    for (;;) {
        alpha -= std::numbers::pi/16;
        cube1->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        
        e.drawCall();
    }
}
