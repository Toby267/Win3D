#include "renderer/Renderer.hpp"

#include "graphicsPipeline/GraphicsPipeline.hpp"

#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

the user passes in objects in the range of (-800, -450, 0) to (800, -450, depth)
the aspect ratio is constant
in object space each object is centred around (0, 0, 0), so even if an object is at z = depth, the half that is visible can still be rendered
the objects are translated to world space, and then to camera space, and then to the canonical view cube
the canonical view cube transformation matrix assumes l = -r, t = -b, & f = -n; and is from (-1, -1, -1) to (1, 1, 1)
    this would mean that the z values for the canonical view cube range from -depth/2 to depth/2
    that is silly, so i double the depth of the camera, and when im doing clipping, I pretend that the canonical view cub is from (-1, -1, 0) to (1, 1, 1)
The viewport transformation then maps (-1, -1, -1) to (1, 1, 1) to the width and height of the screen (should probably change this to map from the above fake canonical view cube)
    it also assumes +y is up, +x is right, and +z is into the screen, so it actually renderes frames upsidown, and the viewport transformation flips it


*/



Renderer::Renderer(int width, int height, int depth, int FieldOfView, std::shared_ptr<Scene> s) :
    width(width), height(height), depthOfField(2*depth), FieldOfView(FieldOfView), scene(s)
{
    scene->setDepthOfField(depthOfField);
}

void Renderer::drawCall() {
    bitmap.clear();

    GraphicsPipeline::DrawCall(*scene, bitmap, viewport);

    window.update(bitmap.getFrameBuffer());
}
