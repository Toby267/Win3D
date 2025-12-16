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

Projection::Projection(double apperatureWidth, double apperatureHeight, double depthOfField, double fieldOfView, double focalDistance)
    : apperatureWidth(apperatureWidth), apperatureHeight(apperatureHeight),
    fieldOfView((60.0 / 360.0) * 2*std::numbers::pi),
    nearFocalDistance(focalDistance), farFocalDistance(focalDistance+depthOfField)
{

}

Matrix Projection::getTransformationMatrix() {
    return Matrix::perspective(nearFocalDistance, farFocalDistance, apperatureHeight/2, apperatureWidth/2, fieldOfView);
}

// * ------------------------------------------- [ VIEWPORT ] ------------------------------------------- * //

Viewport::Viewport(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight)
{
    
}

Matrix Viewport::getTransformationMatrix() {
    return Matrix::translate(screenWidth/2.0, screenHeight/2.0, 10000) * Matrix::scale(screenWidth/2.0, -screenHeight/2.0, 10000);
}