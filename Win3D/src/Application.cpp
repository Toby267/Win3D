#include "Application.hpp"

#include "engine/Engine.hpp"
#include "scene/Materials.hpp"
#include "scene/Mesh.hpp"
#include "util/Colour.hpp"
#include "util/Vector.hpp"
#include <chrono>
#include <iostream>
#include <numbers>

// features:
// got:
// dynamic scenes
// raster renderer /w triangle colour interpolation
// ray casting renderer /w triangle colour interpolation
// getting:
// bxdf material system
// bvh optimisation
// gamma correction
// might get:
// cpu multi-threading
// raster optimisations


//A Hybrid rasterizer Ray-Caster Renderer for Dynamic Scenes on the CPU

/*
TODO:
    - make the ray caster use the same fov as the rasterizer
    - make the rasterizer take in a std::vector of triangles instead of objects, that way the scene class handles all mesh transformations
    - make the bvh sort based on a std::vector of triangles, it is more efficient this way and will compliment the above

    + calculate base colour of a ray-triangle intersection based on its uv coordinates and vertex colours
    - implement brdfs
    + hook brdfs into the ray caster

    - do some testing to get the caster super efficient and the perfect hyperparameters for bvh construction
    - turn it into a hybrid raster caster renderer - only parameter i have left to sync between the two is fov (you can see a difference if screen dimensions is set to 720p)
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
    Engine e = Engine(1920, 1080);
    Scene& scene = e.getScene();

    // Vector a{};
    // Vector b{};
    // Vector c{};
    // Vector d{};

    // Mat::Material hi = Mat::DisneyDiffuse{Colour{}, 0.0, 0.0};
    // Colour adskfas = eval(hi, a, b, c);

    // Mesh* triangle = scene.addObject(Mesh::triangle());
    // triangle->setTranslation(Matrix::translate(0, 0, 2800));
    // triangle->setScale(Matrix::scale(500, 500, 1));

    Mesh* cube1 = scene.addObject(Mesh::cube());
    cube1->setTranslation(Matrix::translate(0, 0, 1100));

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

    // double roughness = 0.0;
    // double subsurface = 0.0;

    for (int i = 0; i < frames; i++) {
        // roughness += 0.1;
        // if (roughness > 1.0) {
        //     roughness = 0.0;
        //     subsurface += 0.1;

        //     if (subsurface > 1.0) {
        //         break;
        //     }
        // }
        alpha -= std::numbers::pi/16;
        // triangle->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
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
