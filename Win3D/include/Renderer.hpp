#pragma once

#include "Window.hpp"

//TODO: make this a singleton when turning it into a library, as only one instance of raylib ever exists.
class Renderer {
private:
    int width, height;

    Window* window;
    double* zBuffer;

public:
    //constructors/destructor
    Renderer(int width, int height);
    ~Renderer();

    //getters/setters

    //public methods
    void test();

private:
    //private methods
};