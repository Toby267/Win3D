// #pragma once

// #include <vector>

// #include "scene/CameraRayTracer.hpp"
// #include "Bitmap3D.hpp"
// #include "Window.hpp"
// #include "graphicsPipeline/Rasterizer.hpp"
// #include "graphicsPipeline/RayTracer.hpp"

// /*
// The rendering engine, consisting of the window to be drawn to, the bitmap to store a frame, and the pipeline to process scenes
// */
// class Renderer {
// private:
//     double width;
//     double height;

//     Window window;
//     Bitmap3D bitmap;

//     Camera camera;
//     // Viewport viewport;

//     // Rasterizer rasterizer;

//     // RayTracer tracer;

// public:
//     //constructors/destructor
//     Renderer(int screenWidth, int screenHeight);

//     //public methods
//     void drawCall(std::vector<Object> objects);

// private:
//     //private methods
//     void drawCallRaster(std::vector<Object> objects);
//     void drawCallRayTraced(std::vector<Object> objects);

//     //geometry processing functions
//     void processGeometry(std::vector<Object>& objects);
//     void processGeometryRayTracing(std::vector<Object>& objects);
// };