#include "scene/Camera.hpp"
#include <exception>
#include <iostream>

Camera::Camera(Vector position, Vector direction, Vector up)
    : position(position), direction(direction), up(up)
{

}

Matrix Camera::getProjection() const {
    return projection;
}

Matrix Camera::getTransformation() const {
    Matrix changeOfBasis = Matrix::changeOfBasis(position, direction, up);
    Matrix translation = Matrix::translate(-position.x(), -position.y(), -position.z());
    
    return changeOfBasis * translation;
}

void Camera::setDepthOfField(int depth) {
    this->depthOfField = depth;

    std::cout << "depth << " << depth << '\n';

    projection = Matrix::perspective(-width/2, -height/2, -depthOfField/2, width/2, height/2, depthOfField/2);
    // projection = Matrix::orthographic(-width/2, -height/2, -depthOfField/2, width/2, height/2, depthOfField/2);
}

void Camera::setDirection(Vector direction) {
    this->direction = direction;
}

void Camera::setUp(Vector up) {
    this->up = direction;
}