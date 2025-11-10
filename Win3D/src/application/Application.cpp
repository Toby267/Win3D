#include "application/Application.hpp"

#include "renderer/Renderer.hpp"

Application::Application() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    std::shared_ptr<Object3D> cube = std::make_shared<Object3D>(Object3D::cube());
    cube->setScale(Matrix::scale(100, 100, 100));
    cube->setTranslation(Matrix::translate(0, 0, 500));
    cube->setRotation(Matrix::rotation(0, -std::numbers::pi/16, -std::numbers::pi/16));
    scene->addObject(cube);

    double alpha = 0.0;

    Renderer* r = new Renderer(1280, 720, scene);

    for (;;) {
        alpha += std::numbers::pi/512;
        cube->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));

        r->drawCall();
    }
}
