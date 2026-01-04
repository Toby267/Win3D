#pragma once

#include "renderer/Camera.hpp"
#include "engine/Bitmap3D.hpp"
#include "scene/Mesh.hpp"
#include "renderer/Ray.hpp"

class CameraRayTracer {
private:
    Camera camera{};

    std::vector<Ray> rays = std::vector<Ray>();

public:
    void trace(std::vector<Mesh>& objects, Bitmap3D& bmap);
};
