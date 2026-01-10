#include "engine/Window.hpp"

#include "raylib.h"
#include <algorithm>
#include <thread>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//default constructor, sets up the window with the given width and height
Window::Window(int w, int h) {
    width = w;
    height = h;
    hasUpdated.store(false);
    alive.store(true);
    frameBuffer = new unsigned char[width*height*4];
    
    thread = std::thread(&Window::run, this, &frameBuffer[0], width, height);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//updates the window with the given buffer
void Window::update(const std::vector<unsigned char>& renderBuffer) {
    if (!alive) return;
    std::copy(renderBuffer.begin(), renderBuffer.end(), frameBuffer);
    hasUpdated.store(true);
}

//returns whether or not the window is still 'alive'
bool Window::isAlive() const {
    return alive.load();
}

//closes the window
void Window::close() {
    thread.join();
    delete[] frameBuffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ---------------------------------------- [ PRIVATE METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//used to constantly render a bitmap pointer onto the screen via raylib
void Window::run(unsigned char* bmap, int width, int height) {
    Image img = {0};
    img.data = bmap;
    img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    img.width = width;
    img.height = height;
    img.mipmaps = 1;

    InitWindow(width, height, "Toby Hothersall - Win3D");
    SetTargetFPS(60);

    while (!WindowShouldClose() && alive.load()) {
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
    alive.store(false);
}
