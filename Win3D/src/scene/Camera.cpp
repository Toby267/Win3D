#include "scene/Camera.hpp"
#include <cmath>

Matrix Camera::getProjection() const {
    return projection;
}

Matrix Camera::getTransformation() const {
    return Matrix::translate(-position[0], -position[1], -position[2]);

    //none of below works yet

    double xAngle = Vector::cosAngle(Vector(1, 0, 0), direction);
    double yAngle = Vector::cosAngle(Vector(0, 1, 0), direction);
    double zAngle = Vector::cosAngle(Vector(0, 0, 1), direction);

    Matrix rotation = Matrix::rotation(std::acos(direction[0]), std::acos(direction[1]), std::acos(direction[2]));
    Matrix translation = Matrix::translate(-position[0], -position[1], -position[2]);
    Matrix retval = translation * rotation;

    return retval;
}