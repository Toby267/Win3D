#include "scene/Camera.hpp"

Camera::Camera():
    projection(Matrix::orthographic(Vector(0, 0, 0), Vector(1280, 720, -1000))),
    position(Vector(0, 0, 0, 1)),
    direction(Vector(0, 0, -1, 0)),
    d(1)
{

}

Camera::Camera(Matrix projection, Vector position, Vector direction, int d):
    projection(projection), position(position), direction(direction), d(d)
{

}

Matrix Camera::getProjection() {
    return projection;
}