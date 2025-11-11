#pragma once

#include "scene/Object3D.hpp"
#include "scene/Camera.hpp"
#include <memory>
#include <vector>

class Scene {
private:
    std::vector<std::shared_ptr<Object3D>> objects;
    std::shared_ptr<Camera> camera;

public:
    //constructors/destructor
    Scene();

    //getters/setters
    const std::vector<std::shared_ptr<Object3D>>& getObjects() const;
    const Camera& getCamera() const;

    //public methods    
    void addObject(std::shared_ptr<Object3D> obj);
    void setCamera(std::shared_ptr<Camera> cam);
    void setDepthOfField(int depth);
};
