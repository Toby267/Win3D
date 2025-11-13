#pragma once

#include <vector>

#include "scene/Object3D.hpp"
#include "graphicsPipeline/GeometryProcessorUtil.hpp"

/*
object space axis:              x = right,  y = up, z = forward
world space axis:               x = right,  y = up, z = forward
camera space axis:              x = right,  y = up, z = forward
canonical view cube axis:       x = right,  y = up, z = forward
screen space axis:              x = right, -y = up, z = forward

object space range:              infinite
world space range:               infinite
camera space range:              infinite
canonical view cube range:       (-1, -1, -1) to (1, 1, 1)
screen space range:              defined by the viewport struct

object space -> world space -> camera space -> canonical view cube -> screen space
*/



class GeometryProcessor {
private:
    struct Camera camera;
    struct Projection projection;
    struct Viewport viewport;

public:
    GeometryProcessor();

    //public methods
    void processGeometry(std::vector<Object3D>& objects);
};