#include "renderer/Camera.hpp"

Matrix Camera::tranformationMatrix() {
    Matrix changeOfBasis = Matrix::changeOfBasis(position, direction, up);
    Matrix translation = Matrix::translate(-position.x(), -position.y(), -position.z());

    return changeOfBasis * translation;
}

Matrix Camera::projectionMatrix() {
    return Matrix::perspective(nearFocalDistance, farFocalDistance, apperatureHeight/2, apperatureWidth/2, fieldOfView);
}

Matrix Camera::viewportMatrix() {
    return Matrix::translate(screenWidth/2.0, screenHeight/2.0, 10000) * Matrix::scale(screenWidth/2.0, -screenHeight/2.0, 10000);
}