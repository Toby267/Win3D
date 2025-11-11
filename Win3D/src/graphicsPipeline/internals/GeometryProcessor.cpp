#include "graphicsPipeline/GraphicsPipelineInternals.hpp"
#include "scene/Scene.hpp"
#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PipelineInternals::processGeometry(const Scene& scene, Bitmap3D& bitmap, const Viewport& viewport) {
    for (const std::shared_ptr<const Object3D>& object : scene.getObjects()) {
        //TODO: surely the GraphicsPipeline::DrawCall() function should just create a copy of the scene, instead of having to create copies of each object here
        Object3D obj = *object;
        
        //step 1 - transform the object into world space
        obj.transform();

        //step 2 - transform the camera to the origin, and take all objects along with it
        obj.applyTransformation(scene.getCamera().getTransformation());

        //step 5 - tesselation
        //this has to happen after step 2 as the z values need to be different. different z values result in different levels of tesselation
        //but it has to happen before the vertex shader so that we have more detail from lighting in the vertex shading stage. for now, we just copy/interpolate vertex colours
        
        //step 4 - vertex shading
        //since we have transformed everything to 'camera space', we can assume that the camera is facing: (0, 0, 1)
        //although we haven't transformed light vectors... so this has to go above. or we just transform light vectors as well, because we are taking copies of the Object3Ds
        

        //step 5 - projection to the canonical view cube
        obj.applyTransformation(scene.getCamera().getProjection());

        //step 6 - clipping

        //step 7 - screen mapping
        obj.applyTransformation(viewport.getTransformation());
        
        //step 8 - the resulting data is passed onto the rasterization stage
        rasterize(bitmap, obj);
    }
}