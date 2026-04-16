#include "engine/Bitmap3D.hpp"

#include <cassert>
#include <cfloat>
#include <fstream>
#include <ios>
#include <vector>

#include "util/Util.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ------------------------------------ [ CONSTRUCTORS/DESCTUCTOR ] ------------------------------------ * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Default constructor taking in the width and height
Bitmap3D::Bitmap3D(int w, int h)
    : width(w), height(h)
{
    frameBuffer = std::vector<unsigned char>(width*height*4, 0);
    zBuffer = std::vector<double>(width*height, DBL_MAX);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// clears the bitmap
void Bitmap3D::clear() {
    for (int i = 0; i < width*height; i++) {
        zBuffer[i] = DBL_MAX;

        frameBuffer[4*i + 0] = 0;
        frameBuffer[4*i + 1] = 0;
        frameBuffer[4*i + 2] = 0;
        frameBuffer[4*i + 3] = 255;
    }
}

// draws a pixel onto the frame buffer
void Bitmap3D::drawPixel(int x, int y, int z, Colour c) {
    if (x >= width || x < 0 || y >= height || y < 0) return;
    z += 20000;
    if (zBuffer[y*width + x] < z) return;

    zBuffer[y*width + x] = z;
    
    int i = 4 * (y * width + x);
    frameBuffer[i + 0] = c.r();
    frameBuffer[i + 1] = c.g();
    frameBuffer[i + 2] = c.b();
    frameBuffer[i + 3] = c.a();
}

// set the value of a pixel ignoring the z buffer
void Bitmap3D::setPixel(int x, int y, Colour c) {
    if (x >= width || x < 0 || y >= height || y < 0) return;
    int i = 4 * (y * width + x);
    frameBuffer[i + 0] = c.r();
    frameBuffer[i + 1] = c.g();
    frameBuffer[i + 2] = c.b();
    frameBuffer[i + 3] = c.a();
}

// stores the current contents of the bitmap as a ppm file at the specified file locaiton. Does not create directories for the path
void Bitmap3D::saveAsPPM(std::string path) {
    // open file
    std::ofstream f(RESOURCES_PATH + path, std::ios::binary);
    assert(f);

    f << "P6\n";                            // format
    f << width << ' ' << height << '\n';    // width and height
    f << "255\n";                           // max colour value

    // write data
    for (int i = 0; i < width*height; i++) {
        const char rgb[3] = {
            (char)frameBuffer[4*i + 0],
            (char)frameBuffer[4*i + 1],
            (char)frameBuffer[4*i + 2]
        };
        f.write(rgb, 3);
    }

    // close
    f.close();
}
