#include "Application.hpp"

#include "engine/Engine.hpp"
#include "scene/objects/PointLight.hpp"
#include "util/Util.hpp"
#include "util/WavefrontLoader.hpp"
#include "scene/objects/Mesh.hpp"
#include <chrono>
#include <iostream>
#include <numbers>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ bunny1440_400 ] ----------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Runs the application
 */
void Apps::speedTestApp(int width, int height, RenderType type, std::string meshPath) {    
    Engine e{width, height, type};
    Scene& scene = e.getScene();

    /* ----------------------------------------- scene ----------------------------------------- */

    Mesh* cube1 = scene.addObject(Wavefront::loadWavefront(meshPath + ".obj", Colour::white() * 0.6));
    cube1->setTranslation(Matrix::translate(0, 0, 1100));

    scene.addLight(PointLight(Vector(1100, 0, 0), Colour{255, 55, 55}));
    scene.addLight(PointLight(Vector(-1100, 0, 0), Colour{55, 255, 55}));

    /* ----------------------------------------- rendering and testing ----------------------------------------- */

    double alpha = 0.0;
    const int frames = 10;
    
    auto start = std::chrono::high_resolution_clock::now();

    // render loop
    for (int i = 0; i < frames; i++) {
        alpha -= std::numbers::pi/16;
        cube1->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));
        
        e.drawCall();
    }

    // calcs statistics
    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
    double fps = frames / duration.count();
    double timePeriod = duration.count() / frames;
    std::cout << "fps: " << fps << "\tT = " << timePeriod << '\n';
}

void Apps::bunnyApp(RenderType type) {
    Engine e{800, 600, type};
    Scene& scene = e.getScene();

    /* ----------------------------------------- scene ----------------------------------------- */

    Mesh* cube1 = scene.addObject(Wavefront::loadWavefront("bunny_86426.obj", Colour::white() * 0.6));
    cube1->setScale(Matrix::scale(200, 200, 200));
    cube1->setTranslation(Matrix::translate(-50, -100, 1000));
    cube1->setRotation(Matrix::rotation(0, -std::numbers::pi/8, -std::numbers::pi));

    scene.addLight(PointLight(Vector(1100, 0, 0), Colour{255, 55, 55}));
    scene.addLight(PointLight(Vector(-1100, 0, 0), Colour{55, 255, 55}));

    /* ----------------------------------------- rendering ----------------------------------------- */

    e.drawCall();
}

void Apps::triangleApp(RenderType type) {
    Engine e{800, 600, type};
    Scene& scene = e.getScene();

    /* ----------------------------------------- scene ----------------------------------------- */

    Mesh* cube1 = scene.addObject(Mesh::triangle());
    cube1->setScale(Matrix::scale(250, 500, 200));
    cube1->setTranslation(Matrix::translate(0, -250, 1000));

    scene.addLight(PointLight(Vector(1100, 0, 0), Colour{255, 55, 55}));
    scene.addLight(PointLight(Vector(-1100, 0, 0), Colour{55, 255, 55}));

    /* ----------------------------------------- rendering ----------------------------------------- */

    e.drawCall();
}