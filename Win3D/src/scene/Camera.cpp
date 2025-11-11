#include "scene/Camera.hpp"
Matrix Camera::getProjection() const {
    return projection;
}

Matrix Camera::getTransformation() const {
    Matrix changeOfBasis = Matrix::changeOfBasis(position, direction, up);
    Matrix translation = Matrix::translate(-position[0], -position[1], -position[2]);
    
    return changeOfBasis * translation;
}