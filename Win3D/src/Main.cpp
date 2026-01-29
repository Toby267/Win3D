#include "Application.hpp"
#include "util/WavefrontLoader.hpp"

//Driver code
int main(int argc, char *argv[]) {
    Wavefront::loadWavefront("Cube.obj");
    
    // Application* app = new Application();
    // delete app;

    return 0;
}
