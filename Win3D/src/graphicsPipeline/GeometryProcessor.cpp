#include "graphicsPipeline/GeometryProcessor.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeometryProcessor::GeometryProcessor() {
    //camera default values
    camera = Camera(
        Vector(0, 0, 0, 1),
        Vector(0, 0, 1, 0),
        Vector(0, 1, 0, 0)
    );

    //projection default values
    projection = Projection(1600, 900, 2000, 60, 1000);

    //viewport default values
    viewport = Viewport(1280, 720);
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
        obj.applyAffineTransformation(camera.getTransformationMatrix());

        //step 3 - vertex shading

        //step 3 - transform the objects to clip space
        obj.applyTransformation(projection.getTransformationMatrix());

        //step 5 - clip the objects
        obj.clip();

        //step 6 - transform the objects to screen space
        obj.applyAffineTransformation(viewport.getTransformationMatrix());
    }
}

void GeometryProcessor::processGeometryRayTracing(std::vector<Object3D>& objects) {
    for (Object3D& obj : objects) {
        //step 0 - tesselation

        //step 1 - transform the object into world space
        obj.transform();

        //step 2 - transform the objects to camera space
        obj.applyAffineTransformation(camera.getTransformationMatrix());

        //step 3 - vertex shading
    }
}
