#include "graphicsPipelineOop/GraphicsPipelineClass.hpp"
#include <vector>

void GraphicsPipelineClass::drawCall(std::vector<Object3D>& objects, Bitmap3D& bmap) {    

    geometryProcessor.processGeometry(objects);

    rasterizer.rasterize(objects, bmap);
}