#pragma once

#include <vector>

#include "Rasterizer.hpp"
#include "graphicsPipeline/GeometryProcessor.hpp"
#include "renderer/Bitmap3D.hpp"

class GraphicsPipeline {
private:
    GeometryProcessor geometryProcessor{};
    Rasterizer rasterizer;

public:
    //constructors/destructor
    GraphicsPipeline(Bitmap3D& bmap);

    //public methods
    void drawCall(std::vector<Object3D>& objects);
};



/*
TODO:

tesselation
clipping & culling
fragment shader
*/