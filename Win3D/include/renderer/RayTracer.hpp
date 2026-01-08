#pragma once

#include "engine/Bitmap3D.hpp"
#include "scene/Scene.hpp"

class RayTracer {
private:
    Scene& scene;

public:
    RayTracer(Scene& sceneRef);

    void trace(Bitmap3D& bmap);
};
