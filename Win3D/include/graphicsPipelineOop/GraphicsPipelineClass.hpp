#pragma once

#include "RasterizerClass.hpp"
#include "graphicsPipelineOop/GeometryProcessorClass.hpp"

#include "renderer/Bitmap3D.hpp"
#include <vector>

class GraphicsPipelineClass {
private:
    GeometryProcessorClass geometryProcessor = GeometryProcessorClass();
    RasterizerClass rasterizer;

public:

    void drawCall(std::vector<Object3D>& objects, Bitmap3D& bmap);

};