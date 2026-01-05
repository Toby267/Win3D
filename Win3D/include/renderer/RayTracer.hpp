#pragma once

#include "engine/Bitmap3D.hpp"
#include "renderer/Ray.hpp"
#include "scene/Scene.hpp"

class RayTracer {
private:
    Scene& scene;

    std::vector<Ray> rays = std::vector<Ray>();

public:
    RayTracer(Scene& sceneRef);

    void trace(Bitmap3D& bmap);
};
