#pragma once

#include "renderer/Camera.hpp"
#include "scene/Mesh.hpp"
#include "scene/BvhNode.hpp"
#include "scene/PointLight.hpp"

#include <vector>

class Scene {
private:
    std::vector<Mesh*> objects{};
    std::vector<PointLight> lights{};
    Camera camera{};

    BvhNode* tree = nullptr;

public:
    //constructors/destructor
    Scene(int screenWidth, int screenHeight);
    Scene() = default;
    ~Scene();

    //getters/setters
    const Camera& getCam() const;
    const std::vector<PointLight>& getLights() const;
    const std::vector<Mesh*>& getObjects() const; //should find a way to just return the triangles straight up so that the rasterizer can't modify the meshes
    //should use a memory arena or a big std::vector of triangles which the meshes and bvh tree point into
    //the whole point of this class is to mange meshes/triangles in a memory efficient and time efficient manor
    
    //public methods
    Mesh* addObject(Mesh* mesh);

    void toCameraSpace();
    void toViewportSpace();
    
    bool intersect(const Ray& ray, HitRecord& rec) const;
    void cleanup();    
};