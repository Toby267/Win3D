#include "graphicsPipeline/GraphicsPipelineInternals.hpp"
#include "scene/Scene.hpp"
#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void processGeometry(const Scene& scene, Bitmap3D& bitmap, const Viewport& viewport) {
    for (const std::shared_ptr<const Object3D>& object : scene.getObjects()) {
        //TODO: surely the GraphicsPipeline::DrawCall() function should just create a copy of the scene, instead of having to create copies of each object here
        Object3D obj = *object;
        
        //step 1 - transform the object into world space
        obj.transform();

        //step 2 - transform the camera to the origin, and take all objects along with it
        obj.applyTransformation(scene.getCamera().getTransformation());

        //step 3 - vertex shading

        //step 4 - projection to the canonical view cube
        obj.applyTransformation(scene.getCamera().getProjection());

        //step 5 - clipping

        //step 6 - screen mapping
        obj.applyTransformation(viewport.getTransformation());
        
        //step 7 - the resulting data is passed onto the rasterization stage
        rasterize(bitmap, obj);
    }
}