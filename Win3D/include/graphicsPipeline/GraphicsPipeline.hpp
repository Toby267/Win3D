#pragma once

#include <vector>

#include "Rasterizer.hpp"
#include "graphicsPipeline/GeometryProcessor.hpp"
#include "renderer/Bitmap3D.hpp"

class GraphicsPipeline {
private:
    GeometryProcessor geometryProcessor = GeometryProcessor();
    Rasterizer rasterizer;

public:

    void drawCall(std::vector<Object3D>& objects, Bitmap3D& bmap);

};