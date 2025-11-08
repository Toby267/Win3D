#include "renderer/VertexShader.hpp"
#include "scene/Scene.hpp"
#include <memory>

void VertexShader::draw(const Scene& scene, Bitmap3D& bitmap) {
    for (const std::shared_ptr<Object3D>& obj : scene.getObjects()) {
        Object3D cpy = *obj;
        cpy.transform();
        cpy.draw(bitmap);
    }
}