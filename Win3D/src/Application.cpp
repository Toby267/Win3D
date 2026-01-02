#include "Application.hpp"

#include <vector>

#include "engine/Engine.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Runs the application
 */
Application::Application() {
    std::vector<Mesh> objects = std::vector<Mesh>();

    Mesh cube1 = Mesh::cube(Colour::blue());
    cube1.setScale(Matrix::scale(100, 100, 100));
    cube1.setTranslation(Matrix::translate(-300, 0, 1100));
    cube1.setRotation(Matrix::rotation(0, 0, 0));

    Mesh sphere = Mesh::icoSphere(Colour::blue());
    sphere.setScale(Matrix::scale(100, 100, 100));
    sphere.setTranslation(Matrix::translate(300, 0, 1000));
    sphere.setRotation(Matrix::rotation(0, 0, 0));
    
    objects.emplace_back(cube1);
    objects.emplace_back(sphere);

    // Renderer* r = new Renderer(1280, 720);
    Engine* e = new Engine();

    double alpha = 0.0;
    double z = 500;

    for (;;) {
        alpha -= std::numbers::pi/16;
        objects[0].setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        // objects[1].setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        // objects[1].setTranslation(Matrix::translate(300, 0, z+=100));

        e->drawCall(objects);

        // std::cin.get();
    }
}
