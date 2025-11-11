#include "application/Application.hpp"

#include "renderer/Renderer.hpp"
#include <memory>

Application::Application() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<Object3D> cube = std::make_shared<Object3D>(Object3D::cube());
    cube->setScale(Matrix::scale(100, 100, 100));
    cube->setTranslation(Matrix::translate(0, 0, 500));
    cube->setRotation(Matrix::rotation(0, 0, 0));

    Vector position     = Vector(0, 200, -100, 1);
    Vector direction    = Matrix::rotation(0, std::numbers::pi/16, 0) * Vector(0, 0, 1, 0);
    Vector up           = Vector(0, 1, 0, 0);
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(position, direction, up);

    scene->addObject(cube);
    scene->setCamera(camera);

    double alpha = 0.0;

    Renderer* r = new Renderer(1280, 720, 1000, 90, scene);

    for (;;) {
        alpha += std::numbers::pi/512;
        cube->setRotation(Matrix::rotation(0, 0, alpha));

        r->drawCall();
    }
}
