#include "Application.hpp"

#include "engine/Engine.hpp"
#include "scene/objects/PointLight.hpp"
#include "util/Util.hpp"
#include "util/WavefrontLoader.hpp"
#include "scene/objects/Mesh.hpp"
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
// reinhard stuff
// exposure stuff
// mutli light averageing
// disney bsdf

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ bunny1440_400 ] ----------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Runs the application
 */
void bunny1440_400::runApp(Engine e) {    
    Scene& scene = e.getScene();

    /* ----------------------------------------- objects ----------------------------------------- */

    Mesh* cube1 = scene.addObject(Wavefront::loadWavefront("bunny_1440.obj", Colour::white() * 0.6));
    cube1->setTranslation(Matrix::translate(0, 0, 1100));

    /* ----------------------------------------- lights ----------------------------------------- */

    // scene.addLight(PointLight(Vector(0, 1000, 1100), Colour::white()));
    // scene.addLight(PointLight(Vector(1100, 0, 0), Colour{255, 55, 55}));
    // scene.addLight(PointLight(Vector(-1100, 0, 0), Colour{55, 255, 55}));

    // scene.addLight(PointLight(Vector(0, 1000, 1100), Colour{255, 0, 0}));
    // scene.addLight(PointLight(Vector(0, 0, 0), Colour{55, 155, 55}));

    scene.addLight(PointLight(Vector(1100, 0, 0), Colour{255, 55, 55}));
    scene.addLight(PointLight(Vector(-1100, 0, 0), Colour{55, 255, 55}));

    // scene.addLight(PointLight(Vector(0, 0, 0), Colour::white()));

    /* ----------------------------------------- rendering and testing ----------------------------------------- */

    double alpha = 0.0;
    const int frames = 25;
    
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < frames; i++) {
        alpha -= std::numbers::pi/16;
        cube1->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        
        e.drawCall();

        // std::cin.get();
    }

    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
    double fps = frames / duration.count();
    std::cout << "fps: " << fps << '\n';
}
