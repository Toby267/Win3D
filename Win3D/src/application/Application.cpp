#include "application/Application.hpp"

#include "renderer/Renderer.hpp"
#include <memory>

Application::Application() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<Object3D> cube1 = std::make_shared<Object3D>(Object3D::cube(Colour::blue()));
    cube1->setScale(Matrix::scale(100, 100, 100));
    cube1->setTranslation(Matrix::translate(0, 0, 1100));
    cube1->setRotation(Matrix::rotation(0, 0, 0));

    std::shared_ptr<Object3D> cube2 = std::make_shared<Object3D>(Object3D::cube(Colour::blue()));
    cube2->setScale(Matrix::scale(100, 100, 100));
    cube2->setTranslation(Matrix::translate(-500, 0, 500));
    cube2->setRotation(Matrix::rotation(0, 0, 0));

    std::shared_ptr<Object3D> cube3 = std::make_shared<Object3D>(Object3D::cube(Colour::blue()));
    cube3->setScale(Matrix::scale(100, 100, 100));
    cube3->setTranslation(Matrix::translate(500, 0, 500));
    cube3->setRotation(Matrix::rotation(0, 0, 0));

    Vector position     = Vector(0, 0, 0, 1);
    Vector direction    = Matrix::rotation(0, 0, 0) * Vector(0, 0, 1, 0);
    Vector up           = Vector(0, 1, 0, 0);
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(position, direction, up);

    scene->addObject(cube1);
    scene->addObject(cube2);
    scene->addObject(cube3);
    scene->setCamera(camera);

    double alpha = 0.0;

    Renderer* r = new Renderer(1280, 720, 1000, 90, scene);

    for (;;) {
        alpha -= std::numbers::pi/256;
        cube1->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        cube2->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        cube3->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));

        // camera->setDirection(Matrix::rotation(0, 0, alpha) * Vector(0, 0, 1, 0));

        r->drawCall();
    }
}
