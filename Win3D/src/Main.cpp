#include "Renderer/Renderer.hpp"

int main(int argc, char *argv[]) {
    Renderer* r = new Renderer(1280, 720);
    delete r;

    return 0;
}
