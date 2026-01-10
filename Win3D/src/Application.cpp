#include "Application.hpp"

#include "engine/Engine.hpp"
#include <chrono>
#include <iostream>
#include <numbers>

//A Hybrid rasterizer Ray-Caster Renderer for Dynamic Scenes on the CPU

/*
TODO:
    - make the ray caster use the same fov as the rasterizer
    - make the rasterizer take in a std::vector of triangles instead of objects, that way the scene class handles all mesh transformations
    - make the bvh sort based on a std::vector of triangles, it is more efficient this way and will compliment the above

    - calculate base colour of a ray-triangle intersection based on its uv coordinates and vertex colours
    - implement brdfs
    - hook brdfs into the ray caster

    - do some testing to get the caster super efficient and the perfect hyperparameters for bvh construction
    - turn it into a hybrid raster caster renderer
    - implement rasterizer optimisations and get it really efficient

    - import blender objects and make some scenes
    - implement thread pool for the caster
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Runs the application
 */
Application::Application() {
    Engine e{};
    Scene& scene = e.getScene();

    Mesh* cube1 = scene.addObject(Mesh::cube(Colour::blue()));
    cube1->setTranslation(Matrix::translate(0, 0, 2800));

    // Mesh* cube2 = scene.addObject(Mesh::cube(Colour::blue()));
    // cube2->setTranslation(Matrix::translate(-400, 0, 1100));

    // Mesh* cube3 = scene.addObject(Mesh::cube(Colour::blue()));
    // cube3->setTranslation(Matrix::translate(400, 0, 1100));

    // Mesh* cube4 = scene.addObject(Mesh::cube(Colour::blue()));
    // cube4->setTranslation(Matrix::translate(800, 0, 1100));

    // Mesh* sphere = scene.addObject(Mesh::icoSphere(Colour::blue()));
    // sphere->setTranslation(Matrix::translate(0, 0, 1000));

    double alpha = 0.0;
    const int frames = 50;
    
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < frames; i++) {
        alpha -= std::numbers::pi/16;
        cube1->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        // cube2->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        // cube3->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        // cube4->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        // sphere->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        
        e.drawCall();
    }

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
    double fps = frames / duration.count();
    std::cout << "fps: " << fps << '\n';
}
