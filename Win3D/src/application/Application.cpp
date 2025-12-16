#include "application/Application.hpp"

#include <iostream>
#include <vector>

#include "renderer/Renderer.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Runs the application
 */
Application::Application() {
    std::vector<Object3D> objects = std::vector<Object3D>();

    Object3D cube1 = Object3D::cube(Colour::blue());
    cube1.setScale(Matrix::scale(100, 100, 100));
    cube1.setTranslation(Matrix::translate(-300, 0, 1100));
    cube1.setRotation(Matrix::rotation(0, 0, 0));

    Object3D sphere = Object3D::icoSphere(Colour::blue());
    sphere.setScale(Matrix::scale(100, 100, 100));
    sphere.setTranslation(Matrix::translate(300, 0, 1000));
    sphere.setRotation(Matrix::rotation(0, 0, 0));
    
    objects.emplace_back(cube1);
    objects.emplace_back(sphere);

    Renderer* r = new Renderer(1280, 720);

    double alpha = 0.0;
    double z = 500;

    for (;;) {
        alpha -= std::numbers::pi/256;
        objects[0].setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        objects[1].setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        // objects[1].setTranslation(Matrix::translate(300, 0, z+=100));

        r->drawCall(objects);

        // std::cin.get();
    }
}
