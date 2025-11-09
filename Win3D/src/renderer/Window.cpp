#include "renderer/Window.hpp"

#include "raylib.h"
#include <algorithm>
#include <thread>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Window::Window(int width, int height) {
    this->width = width;
    this->height = height;
    this->hasUpdated.store(false);
    this->shouldStop.store(false);
    this->frameBuffer = new unsigned char[width*height*4];
    
    t = std::thread(&Window::run, this, &frameBuffer[0], width, height);
}

Window::~Window() {
    close();
    delete[] frameBuffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::update(const std::vector<unsigned char>& renderBuffer) {
    std::copy(renderBuffer.begin(), renderBuffer.end(), frameBuffer);
    hasUpdated.store(true);
}

void Window::close() {
    shouldStop.store(true);
    t.join();
}

bool Window::isAlive() {
    return !shouldStop.load();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ PRIVATE METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::run(unsigned char* bmap, int width, int height) {
    Image img = {0};
    img.data = bmap;
    img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    img.width = width;
    img.height = height;
    img.mipmaps = 1;

    InitWindow(width, height, "Toby Hothersall - Win3D");
    SetTargetFPS(60);

    while (!WindowShouldClose() && !shouldStop.load()) {
        if (hasUpdated.load()) {
            BeginDrawing();
    
            Texture2D tex = LoadTextureFromImage(img);
            DrawTexture(tex, 0, 0, WHITE);
            hasUpdated.store(false);
    
            EndDrawing();

            UnloadTexture(tex);
        }
    }
    CloseWindow();
    close();
}
