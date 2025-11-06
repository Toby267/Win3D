#pragma once

#include "Bitmap3D.hpp"
#include "Window.hpp"

//TODO: make this a singleton when turning it into a library, as only one instance of raylib ever exists.
class Renderer {
private:
    int width, height;

    Window window;
    Bitmap3D bitmap;

public:
    //constructors/destructor
    Renderer(int width, int height);

    //public methods
    void test();

private:
    //private methods
};