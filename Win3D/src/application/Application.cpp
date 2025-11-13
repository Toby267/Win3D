#include "application/Application.hpp"

#include <vector>

#include "renderer/Renderer.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Runs the application
 */
Application::Application() {
    std::vector<Object3D> objects;

    Object3D cube1 = Object3D::cube(Colour::blue());
    cube1.setScale(Matrix::scale(100, 100, 100));
    cube1.setTranslation(Matrix::translate(0, 0, 1100));
    cube1.setRotation(Matrix::rotation(0, 0, 0));

    Object3D cube2 = Object3D::cube(Colour::blue());
    cube2.setScale(Matrix::scale(100, 100, 100));
    cube2.setTranslation(Matrix::translate(-500, 0, 500));
    cube2.setRotation(Matrix::rotation(0, 0, 0));

    Object3D cube3 = Object3D::cube(Colour::blue());
    cube3.setScale(Matrix::scale(100, 100, 100));
    cube3.setTranslation(Matrix::translate(500, 0, 500));
    cube3.setRotation(Matrix::rotation(0, 0, 0));

    objects.emplace_back(cube1);
    objects.emplace_back(cube2);
    objects.emplace_back(cube3);

    Renderer* r = new Renderer(1280, 720);

    double alpha = 0.0;

    for (;;) {
        alpha -= std::numbers::pi/256;
        objects[0].setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        objects[1].setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        objects[2].setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));

        r->drawCall(objects);
    }
}
