#include "graphicsPipeline/GeometryProcessor.hpp"

/**
 * Calculates the transformatin matrix to transform objects from world space to camera space
 * 
 * @return the transformation matrix
 */
Matrix Camera::transformation() {
    Matrix changeOfBasis = Matrix::changeOfBasis(position, direction, up);
    Matrix translation = Matrix::translate(-position.x(), -position.y(), -position.z());
    
    return changeOfBasis * translation;
}

/**
 * Calculates the transformation matrix to transform objects from camera space to clip space
 * 
 * @return the transformation matrix
 */
Matrix Projection::transformation() {
    return Matrix::perspective(-lensWidth/2, -lensHeight/2, -depthOfField/2, lensWidth/2, lensHeight/2, depthOfField/2);
}

/**
 * Calculates the transformation matrix to transform objects from clip space to screen space
 * 
 * @return the transformation matrix
 */
Matrix Viewport::transformation() {
    return Matrix::translate(screenWidth/2.0, screenHeight/2.0, 10000) * Matrix::scale(screenWidth/2.0, -screenHeight/2.0, 10000);
}

/**
 * Performs geometry processing on the given objects, this includes tesselation, and vertex shading
 * 
 * @param objexts the vector of objects
 */
void GeometryProcessor::processGeometry(std::vector<Object3D>& objects) {
    for (Object3D& obj : objects) {
        //step 0 - tesselation

        //step 1 - transform the object into world space
        obj.transform();

        //step 2 - transform the objects to camera space
        obj.applyAffineTransformation(camera.transformation());

        //step 3 - vertex shading

        //step 3 - transform the objects to clip space
        obj.applyTransformation(projection.transformation());

        //step 5 - clip the objects
        obj.clip();

        //step 6 - transform the objects to screen space
        obj.applyAffineTransformation(viewport.transformation());
    }
}
