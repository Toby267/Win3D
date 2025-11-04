#pragma once

#include "Window.hpp"

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