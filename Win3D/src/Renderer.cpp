#include "Renderer.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer::Renderer(int width, int height) {
    window = new Window(width, height);
    zBuffer = new double[width*height];

    while (window->isAlive()) {
        unsigned char frameBuffer[width*height*4];
        
        int num = rand() % 3;

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int i = 4 * (y * width + x);
                frameBuffer[i + 0] = num == 0 ? 255 : 0;
                frameBuffer[i + 1] = num == 1 ? 255 : 0;
                frameBuffer[i + 2] = num == 2 ? 255 : 0;
                frameBuffer[i + 3] = 255;
            }
        }
        window->update(frameBuffer);
        
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

Renderer::~Renderer() {
    delete window;
    delete zBuffer;
}
