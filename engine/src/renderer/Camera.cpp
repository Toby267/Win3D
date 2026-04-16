#include "renderer/Camera.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// returns the world space to camera space transformation matrix
Matrix Camera::tranformationMatrix() const {
    Matrix changeOfBasis = Matrix::changeOfBasis(position, direction, up);
    Matrix translation = Matrix::translate(-position.x(), -position.y(), -position.z());

    return changeOfBasis * translation;
}

// returns the rotation part of the camera space transformation matrix
Matrix Camera::rotationMatrix() const {
    return Matrix::changeOfBasis(position, direction, up);
}

// calculates and returns the projection matrix
Matrix Camera::projectionMatrix() const {
    return Matrix::perspective(nearFocalDistance, farFocalDistance, apperatureWidth / apperatureHeight, fieldOfView);
    // return Matrix::orthographic(nearFocalDistance, farFocalDistance, apperatureHeight/2, apperatureWidth/2);
}

// calculates and returns the viewport transform matrix translating from ndc coordinates to the screen
Matrix Camera::viewportMatrix() const {
    return Matrix::translate(screenWidth/2.0, screenHeight/2.0, 10000) * Matrix::scale(screenWidth/2.0, -screenHeight/2.0, 10000);
}
