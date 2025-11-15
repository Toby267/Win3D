#include "graphicsPipeline/GeometryProcessorUtil.hpp"

#include "util/Matrix.hpp"

// * -------------------------------------------- [ CAMERA ] -------------------------------------------- * //

Camera::Camera(Vector position, Vector direction, Vector up)
    : position(position), direction(direction), up(up)
{
    
}

Matrix Camera::getTransformationMatrix() {
    Matrix changeOfBasis = Matrix::changeOfBasis(position, direction, up);
    Matrix translation = Matrix::translate(-position.x(), -position.y(), -position.z());

    return changeOfBasis * translation;
}

// * ------------------------------------------ [ PROJECTION ] ------------------------------------------ * //

Projection::Projection(double lensWidth, double lensHeight, double depthOfField, double fieldOfView)
    : lensWidth(lensWidth), lensHeight(lensHeight), depthOfField(depthOfField), fieldOfView(fieldOfView)
{

}

Matrix Projection::getTransformationMatrix() {
    return Matrix::perspective(-lensWidth/2, -lensHeight/2, -depthOfField/2, lensWidth/2, lensHeight/2, depthOfField/2);
}

// * ------------------------------------------- [ VIEWPORT ] ------------------------------------------- * //

Viewport::Viewport(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight)
{
    
}

Matrix Viewport::getTransformationMatrix() {
    return Matrix::translate(screenWidth/2.0, screenHeight/2.0, 10000) * Matrix::scale(screenWidth/2.0, -screenHeight/2.0, 10000);
}