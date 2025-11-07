#pragma once

#include "Bitmap3D.hpp"
#include "Window.hpp"
#include <memory>

//TODO: make this a singleton when turning it into a library, as only one instance of raylib ever exists.
class Renderer {
private:
    int width, height;

    std::unique_ptr<Window> window;
    std::unique_ptr<Bitmap3D> bitmap;

public:
    //constructors/destructor
    Renderer(int width, int height);

    //public methods
    void test();

private:
    //private methods
    void drawCall();
};