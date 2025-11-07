#pragma once

#include <memory>
#include <thread>

/**
 * Class representing a raylib window, its byte array, and related data. 
 *
 * The window has its own thread for drawing to the windows based on the byte array.
 */

class Window {
private:
    //attributes
    int width, height;
    unsigned char* frameBuffer;

    std::atomic<bool> hasUpdated;
    std::atomic<bool> shouldStop;
    std::thread t;

public:
    //constructors/destructor
    Window(int width, int height);
    ~Window();

    //public methods
    void update(std::shared_ptr<unsigned char[]> renderBuffer);
    void close();
    bool isAlive();

private:
    //private methods
    void run(unsigned char* bmap, int width, int height);
};