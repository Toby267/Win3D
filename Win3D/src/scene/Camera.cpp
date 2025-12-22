#include "scene/Camera.hpp"

#include "util/Matrix.hpp"

// * -------------------------------------------- [ CAMERA ] -------------------------------------------- * //

Matrix Camera::tranformationMatrix() {
    Matrix changeOfBasis = Matrix::changeOfBasis(position, direction, up);
    Matrix translation = Matrix::translate(-position.x(), -position.y(), -position.z());

    return changeOfBasis * translation;
}
Matrix Camera::projectionMatrix() {
    return Matrix::perspective(nearFocalDistance, farFocalDistance, apperatureHeight/2, apperatureWidth/2, fieldOfView);
}

// * ------------------------------------------- [ VIEWPORT ] ------------------------------------------- * //

Matrix Viewport::tranformationMatrix() {
    return Matrix::translate(screenWidth/2.0, screenHeight/2.0, 10000) * Matrix::scale(screenWidth/2.0, -screenHeight/2.0, 10000);
}