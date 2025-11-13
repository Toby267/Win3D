#pragma once

#include <vector>

#include "util/Vector.hpp"
#include "util/Matrix.hpp"
#include "scene/Object3D.hpp"

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

struct transformation {

};

struct Camera {
    Vector position     = Vector(0, 0, 0, 1);
    Vector direction    = Vector(0, 0, 1, 0);
    Vector up           = Vector(0, 1, 0, 0);

    Matrix transformation();
};

struct Projection {
    double lensWidth  = 1600;
    double lensHeight = 900;
    
    double depthOfField = 2000;
    double fieldOfView  = 90;

    enum type {orthographic, perspctive} projection;

    Matrix transformation();
};

struct Viewport {
    int screenWidth = 1280;
    int screenHeight = 720;

    Matrix transformation();
};

class GeometryProcessor {
private:
    struct Camera camera;
    struct Projection projection;
    struct Viewport viewport;

public:
    void processGeometry(std::vector<Object3D>& objects);
};