#include "graphicsPipeline/GraphicsPipelineInternals.hpp"
#include "scene/Scene.hpp"
#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void processGeometry(const Scene& scene, Bitmap3D& bitmap) {
    for (const std::shared_ptr<const Object3D>& object : scene.getObjects()) {
        //TODO: surely the GraphicsPipeline::DrawCall() function should just create a copy of the scene, instead of having to create copies of each object here
        Object3D obj = *object;
        
        //step 0 - transform the object into world space
        obj.transform();

        //step 1 - vertex shading

        //step 2 - projection
        obj.applyTransformation(scene.getCamera().getProjection());

        //step 3 - clipping

        //step 4 - screen mapping
        
        //TODO: work out where to store the width and height and what not.
        //I assume the renderer will store the width and height of the physical window (the renderer owns the window),
        //and the camera will store the width and height of the viewport (i think it's called), or the AABB box
        int width = bitmap.getWidth(), height = bitmap.getHeight();
        obj.applyTransformation(Matrix::translate(width/2.0, height/2.0, 1000/2.0) * Matrix::scale(width/2.0, -height/2.0, 1000/2.0));
        
        //step 5 - the resulting data is passed onto the rasterization stage
        rasterize(bitmap, obj);
    }
}