#include "graphicsPipeline/GeometryProcessor.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeometryProcessor::GeometryProcessor() {

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
        obj.applyAffineTransformation(camera.tranformationMatrix());

        //step 3 - vertex shading

        //step 3 - transform the objects to clip space
        obj.applyTransformation(camera.projectionMatrix());

        //step 5 - clip the objects
        obj.clip();

        //step 6 - transform the objects to screen space
        obj.applyAffineTransformation(viewport.tranformationMatrix());
    }
}

void GeometryProcessor::processGeometryRayTracing(std::vector<Object3D>& objects) {
    for (Object3D& obj : objects) {
        //step 0 - tesselation

        //step 1 - transform the object into world space
        obj.transform();

        //step 2 - transform the objects to camera space
        obj.applyAffineTransformation(camera.tranformationMatrix());

        //step 3 - vertex shading
    }
}
