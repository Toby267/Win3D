#pragma once

#include "scene/Scene.hpp"
#include "renderer/Bitmap3D.hpp"

/**
 * Takes in the vertex coordinates, uv coordniates, triangle indeces (indeces of the vertex coordinates array), normals encapsulated as an object3D,
 * along with matrix for translation, scale, rotate, and skew, and transforms the object into world space, and calculates the colour at each vertex based on the lights in the scene
 *
 * actually, the colour of the object is defined in the object class, the colour from the lights is figured out in the fragment processor

 * Ideally take in an entire scene as input.
 * Ideally this should be stateless
 */
class VertexShader {
public:
    //public methods
    static void draw(const Scene& scene, Bitmap3D& bitmap);
};