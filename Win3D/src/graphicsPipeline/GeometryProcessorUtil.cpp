#include "graphicsPipeline/GeometryProcessorUtil.hpp"

//recalculates the transformation matrix for the camera transformation
void Camera::calcTransformationMatrix() {
    Matrix changeOfBasis = Matrix::changeOfBasis(position, direction, up);
    Matrix translation = Matrix::translate(-position.x(), -position.y(), -position.z());

    transformation = changeOfBasis * translation;
}

//recalculates the transformation matrix for the projection transformation
void Projection::calcTransformationMatrix() {
    transformation = Matrix::perspective(-lensWidth/2, -lensHeight/2, -depthOfField/2, lensWidth/2, lensHeight/2, depthOfField/2);
}

//recalculates the transformation matrix for the viewport transformation
void Viewport::calcTransformationMatrix() {
    transformation = Matrix::translate(screenWidth/2.0, screenHeight/2.0, 10000) * Matrix::scale(screenWidth/2.0, -screenHeight/2.0, 10000);
}