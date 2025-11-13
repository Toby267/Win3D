#include "graphicsPipeline/GeometryProcessor.hpp"
#include <iostream>

GeometryProcessor::GeometryProcessor() {
    camera.calcTransformationMatrix();
    viewport.calcTransformationMatrix();
    projection.calcTransformationMatrix();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
        obj.applyAffineTransformation(camera.transformation);

        //step 3 - vertex shading

        //step 3 - transform the objects to clip space
        obj.applyTransformation(projection.transformation);

        //step 5 - clip the objects
        obj.clip();

        //step 6 - transform the objects to screen space
        obj.applyAffineTransformation(viewport.transformation);
    }
}
