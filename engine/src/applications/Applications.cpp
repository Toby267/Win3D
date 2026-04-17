#include "Application.hpp"

#include "engine/Engine.hpp"
#include "scene/objects/PointLight.hpp"
#include "util/Util.hpp"
#include "util/Files.hpp"
#include "scene/objects/Mesh.hpp"
#include <chrono>
#include <iostream>
#include <numbers>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------------ [ speedTestApp ] ----------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// runs a given scene for 10 frames calculating the frame rate and time period
void Apps::speedTestApp(int width, int height, RenderType type, std::string meshPath) {    
    Engine* e = new Engine{width, height, type};
    Scene& scene = e->getScene();

    /* ----------------------------------------- scene ----------------------------------------- */

    Mesh* obj = scene.addObject(Files::readWavefront(meshPath + ".obj", Colour::white() * 0.6));
    obj->setTranslation(Matrix::translate(0, 0, 1100));

    scene.addLight(PointLight(Vector(1100, 0, 0), Colour{255, 55, 55}));
    scene.addLight(PointLight(Vector(-1100, 0, 0), Colour{55, 255, 55}));

    /* --------------------------------- rendering and testing --------------------------------- */

    double alpha = 0.0;
    const int frames = 10;
    
    auto start = std::chrono::high_resolution_clock::now();

    // render loop
    for (int i = 0; i < frames; i++) {
        alpha -= std::numbers::pi/16;
        obj->setRotation(Matrix::rotation(0, -std::numbers::pi/8, alpha));

        std::future<bool> complete = std::async(std::launch::async, [e](){
            e->drawCall();
            return true;
        });
    }

    // calcs statistics
    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
    double fps = frames / duration.count();
    double timePeriod = duration.count() / frames;
    std::cout << "fps: " << fps << "\tT = " << timePeriod << '\n';

    std::cout << "Press any key to close: ";
    std::cin.get();
    e->closeWindow();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * -------------------------------------------- [ bunnyApp ] ------------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// displays the bunny mesh with 86426 triangles, at 800x600 resolution, with two point lights
void Apps::bunnyApp(RenderType type) {
    Engine* e = new Engine{800, 600, type};
    Scene& scene = e->getScene();

    /* ----------------------------------------- scene ----------------------------------------- */

    Mesh* bunny = scene.addObject(Files::readWavefront("bunny_86426.obj", Colour::white() * 0.6));
    bunny->setScale(Matrix::scale(200, 200, 200));
    bunny->setTranslation(Matrix::translate(-50, -100, 1000));
    bunny->setRotation(Matrix::rotation(0, -std::numbers::pi/8, -std::numbers::pi));

    scene.addLight(PointLight(Vector(1100, 0, 0), Colour{255, 55, 55}));
    scene.addLight(PointLight(Vector(-1100, 0, 0), Colour{55, 255, 55}));

    /* --------------------------------------- rendering --------------------------------------- */

    std::future<bool> complete = std::async(std::launch::async, [e](){
        e->drawCall();
        return true;
    });

    while (!complete.get());
    std::cout << "Press any key to close: ";
    std::cin.get();
    e->closeWindow();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------------ [ triangleApp ] ------------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// displays the triangle mesh, at 800x600 resolution, where each vertex is a red, green, and blue, and the colours are interpolated on the raster engine
void Apps::triangleApp(RenderType type) {
    Engine* e = new Engine{800, 600, type};
    Scene& scene = e->getScene();

    /* ----------------------------------------- scene ----------------------------------------- */

    Mesh* triangle = scene.addObject(Mesh::triangle());
    triangle->setScale(Matrix::scale(250, 500, 200));
    triangle->setTranslation(Matrix::translate(0, -250, 1000));

    scene.addLight(PointLight(Vector(0, -170, 0), Colour{255, 255, 255} * 0.2));

    /* --------------------------------------- rendering --------------------------------------- */

    std::future<bool> complete = std::async(std::launch::async, [e](){
        e->drawCall();
        return true;
    });

    while (!complete.get());
    std::cout << "Press any key to close: ";
    std::cin.get();
    e->closeWindow();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------------ [ objectsApp ] ------------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// dispalys the head, teapot, and bunny meshes with a total of 54694 triangles, at 1000x500 resolution, with six point lights
void Apps::objectsApp(RenderType type) {
    Engine* e = new Engine{1000, 500, type};
    Scene& scene = e->getScene();

    /* ----------------------------------------- scene ----------------------------------------- */

    Mesh* head = scene.addObject(Files::readWavefront("head_17684.obj", Colour::white() * 0.6));
    head->setTranslation(Matrix::translate(-225, -60, 1000));
    head->setRotation(Matrix::rotation(0, -std::numbers::pi/8, std::numbers::pi));

    Mesh* teapot = scene.addObject(Files::readWavefront("teapot_15404.obj", Colour::white() * 0.6));
    teapot->setTranslation(Matrix::translate(25, -50, 1200));
    teapot->setRotation(Matrix::rotation(0, -std::numbers::pi/8, std::numbers::pi));

    Mesh* bunny = scene.addObject(Files::readWavefront("bunny_21606.obj", Colour::white() * 0.6));
    bunny->setTranslation(Matrix::translate(275, -50, 1200));
    bunny->setRotation(Matrix::rotation(0, -std::numbers::pi/8, std::numbers::pi));

    scene.addLight(PointLight(Vector(1100, -100, 0), Colour{255, 55, 55}));
    scene.addLight(PointLight(Vector(-1100, -100, 0), Colour{55, 255, 55}));

    scene.addLight(PointLight(Vector(1100, 100, 0), Colour{55, 255, 55}));
    scene.addLight(PointLight(Vector(-1100, 100, 0), Colour{55, 55, 255}));

    scene.addLight(PointLight(Vector(1100, 200, 900), Colour{255, 55, 55}));
    scene.addLight(PointLight(Vector(-1100, 200, 900), Colour{55, 255, 55}));

    /* --------------------------------------- rendering --------------------------------------- */

    std::future<bool> complete = std::async(std::launch::async, [e](){
        e->drawCall();
        return true;
    });

    while (!complete.get());
    std::cout << "Press any key to close: ";
    std::cin.get();
    e->closeWindow();
}
