#include "scene/Camera.hpp"
Matrix Camera::getProjection() const {
    return projection;
}

Matrix Camera::getTransformation() const {
    Matrix changeOfBasis = Matrix::changeOfBasis(position, direction, up);
    Matrix translation = Matrix::translate(-position[0], -position[1], -position[2]);
    
    return changeOfBasis * translation;
}

void Camera::setDepthOfField(int depth) {
    this->depthOfField = depth;

    projection = Matrix::perspective(-width/2, -height/2, -depthOfField/2, width/2, height/2, depthOfField/2);
}