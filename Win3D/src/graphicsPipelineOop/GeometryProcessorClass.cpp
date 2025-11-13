#include "graphicsPipelineOop/GeometryProcessorClass.hpp"
#include <iostream>

Matrix CameraS::transformation() {
        Matrix changeOfBasis = Matrix::changeOfBasis(position, direction, up);
        Matrix translation = Matrix::translate(-position.x(), -position.y(), -position.z());
        
        return changeOfBasis * translation;
    }


Matrix Projection::transformation() {
    return Matrix::perspective(-lensWidth/2, -lensHeight/2, -depthOfField/2, lensWidth/2, lensHeight/2, depthOfField/2);
}

Matrix ViewportS::transformation() {
    return Matrix::translate(screenWidth/2.0, screenHeight/2.0, 10000) * Matrix::scale(screenWidth/2.0, -screenHeight/2.0, 10000);
}

//TODO: for now, as your refactoring pass in the bitmap, but remember to remove it later
//the method should ideally just mutate the objects
void GeometryProcessorClass::processGeometry(std::vector<Object3D>& objects) {
    for (Object3D& obj : objects) {
        //step 0 - tesselation

        //step 1 - transform the object into world space
        obj.transform();

        //step 2 - transform the objects to camera space
        obj.applyTransformation(camera.transformation());

        //step 3 - vertex shading

        //step 3 - transform the objects to clip space
        obj.applyTransformation(projection.transformation());

        //step 5 - clip the objects
        obj.clip();

        //step 6 - transform the objects to screen space
        obj.applyTransformation(viewport.transformation());
    }
}
