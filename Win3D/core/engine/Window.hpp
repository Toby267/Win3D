#pragma once

#include <thread>
#include <vector>

/**
 * Class representing a raylib window, its byte array, and related data. 
 *
 * The window has its own thread for drawing to the windows based on the byte array.
 */
class Window {
private:
    int width, height;
    unsigned char* frameBuffer;

    std::atomic<bool> hasUpdated;
    std::atomic<bool> alive;
    std::thread thread;

public:
    //constructors/destructor
    Window(int width, int height);

    //public methods
    void update(const std::vector<unsigned char>& renderBuffer);
    bool isAlive() const;
    void close();

private:
    //private methods
    void run(unsigned char* bmap, int width, int height);
};