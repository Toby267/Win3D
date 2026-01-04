#include "scene/Scene.hpp"

Scene::Scene() {
    Mesh cube1 = Mesh::cube(Colour::blue());
    cube1.setScale(Matrix::scale(100, 100, 100));
    cube1.setTranslation(Matrix::translate(-300, 0, 1100));
    cube1.setRotation(Matrix::rotation(0, 0, 0));

    Mesh sphere = Mesh::icoSphere(Colour::blue());
    sphere.setScale(Matrix::scale(100, 100, 100));
    sphere.setTranslation(Matrix::translate(300, 0, 1000));
    sphere.setRotation(Matrix::rotation(0, 0, 0));

    // objects.emplace_back(cube1);
    objects.emplace_back(sphere);
}

std::vector<Mesh> Scene::getObjects() {
    return objects;
}