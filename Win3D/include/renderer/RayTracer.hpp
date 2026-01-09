#pragma once

#include "engine/Bitmap3D.hpp"
#include "scene/Scene.hpp"

class RayTracer {
private:
    Scene& scene;

public:
    //constructors/destructor
    RayTracer(Scene& sceneRef);

    //public methods
    void trace(Bitmap3D& bmap);
};
