#pragma once

#include "scene/Scene.hpp"
#include "renderer/Bitmap3D.hpp"
#include "renderer/Viewport.hpp"

namespace PipelineInternals {
    // * ------------------------------------------ [ GEOMETRY PROCESSOR ] ------------------------------------------ * //
    
    void processGeometry(const Scene& scene, Bitmap3D& bitmap, const Viewport& viewport);
    
    // * ---------------------------------------------- [ RASTERIZER ] ---------------------------------------------- * //
    
    void rasterize(Bitmap3D&, const Object3D&);
    
    void drawTriangle(Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3, Vector n1, Vector n2, Vector n3);
    void drawTriangle(Bitmap3D& bitmap, Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3); //only use while developing the 3D one
    void drawLine(Bitmap3D& bitmap, Vector start, Vector end, Colour c1, Colour c2);
    
    // * ------------------------------------------ [ FRAGMENT PROCESSOR ] ------------------------------------------ * //
    
    void processFragments();
}