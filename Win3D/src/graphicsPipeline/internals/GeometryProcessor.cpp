#include "graphicsPipeline/GraphicsPipelineInternals.hpp"
#include "scene/Scene.hpp"
#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void processGeometry(const Scene& scene, Bitmap3D& bitmap) {
    for (const std::shared_ptr<const Object3D>& object : scene.getObjects()) {
        Object3D obj = *object;
        
        //step 0 - transform the object into world space
        obj.transform();

        //step 1 - vertex shading

        //step 2 - projection
        obj.applyTransformation(scene.getCamera().getProjection());

        //step 3 - clipping

        //step 4 - screen mapping
        obj.applyTransformation(Matrix::translate(1280/2.0, 720/2.0, 1000/2.0) * Matrix::scale(1280/2.0, -720/2.0, 1000/2.0));
        
        //step 5 - the resulting data is passed onto the rasterization stage
        rasterize(bitmap, obj);
    }
}