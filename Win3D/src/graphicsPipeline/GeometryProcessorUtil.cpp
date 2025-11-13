#include "graphicsPipeline/GeometryProcessorUtil.hpp"

/**
 * Calculates the transformatin matrix to transform objects from world space to camera space
 * 
 * @return the transformation matrix
 */
void Camera::calcTransformationMatrix() {
    Matrix changeOfBasis = Matrix::changeOfBasis(position, direction, up);
    Matrix translation = Matrix::translate(-position.x(), -position.y(), -position.z());

    transformation = changeOfBasis * translation;
}

/**
 * Calculates the transformation matrix to transform objects from camera space to clip space
 * 
 * @return the transformation matrix
 */
void Projection::calcTransformationMatrix() {
    transformation = Matrix::perspective(-lensWidth/2, -lensHeight/2, -depthOfField/2, lensWidth/2, lensHeight/2, depthOfField/2);
}

/**
 * Calculates the transformation matrix to transform objects from clip space to screen space
 * 
 * @return the transformation matrix
 */
void Viewport::calcTransformationMatrix() {
    transformation = Matrix::translate(screenWidth/2.0, screenHeight/2.0, 10000) * Matrix::scale(screenWidth/2.0, -screenHeight/2.0, 10000);
}