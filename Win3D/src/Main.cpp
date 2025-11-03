#include "raylib.h"
#include <chrono>
#include <cstdlib>
#include <thread>

void Run(unsigned char*, int, int);

static bool coloursHaveUpdated = false;

int main(int argc, char *argv[]) {
    const int width = 600, height = 400;
    unsigned char bmap[width*height*4];

    std::thread t(Run, &bmap[0], width, height);

    while (t.joinable()) {
        int num = rand() % 3;
        
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int i = 4 * (y * width + x);
                bmap[i + 0] = num == 0 ? 255 : 0;
                bmap[i + 1] = num == 1 ? 255 : 0;
                bmap[i + 2] = num == 2 ? 255 : 0;
                bmap[i + 3] = 255;
            }
        }
        coloursHaveUpdated = true;

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    return 0;
}

void Run(unsigned char* bmap, int width, int height) {
    Image img = {0};
    img.data = bmap;
    img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    img.width = width;
    img.height = height;
    img.mipmaps = 1;

    InitWindow(width, height, "Toby Hothersall - Win3D");
    SetTargetFPS(30);

    while (!WindowShouldClose()) {
        if (coloursHaveUpdated) {
            BeginDrawing();
    
            Texture2D tex = LoadTextureFromImage(img);
            DrawTexture(tex, 0, 0, WHITE);
            coloursHaveUpdated = false;
    
            EndDrawing();   
        }
    }
    CloseWindow();
}
