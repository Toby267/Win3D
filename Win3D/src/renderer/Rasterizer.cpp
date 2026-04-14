#include "renderer/Renderer.hpp"
#include "scene/core/SceneUtil.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ STATIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void drawTriangle(Bitmap3D& bmap, Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3);
static void drawLine(Bitmap3D& bmap, Vector start, Vector end, Colour c1, Colour c2);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ PUBLIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Performs rasterization on a vector of objects, assuming they are already in screen space, and renders them on a bitmap/framebuffer
 * 
 * @param objects   the objects to rasterize
 * @param bmap      the bitmap to render onto
 */
void Renderer::rasterize(Bitmap3D& bmap, const Scene& scene) {
    for (Mesh* obj : scene.getObjects()) {
        for (Triangle t : obj->getTriangles()) {
            drawTriangle(bmap, t.v1.position, t.v2.position, t.v3.position, t.v1.colour, t.v2.colour, t.v3.colour);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// * ----------------------------------------- [ STATIC METHODS ] ---------------------------------------- * //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Draws a triangle onto a given bitmap, defined by their veritces, and their colours
 * 
 * @param v1, v2, v3    the vertices of the triangle
 * @param c1, c2, c3    the colours of the vertices
 * @param bmap          the bmap to render onto
 */
static void drawTriangle(Bitmap3D& bmap, Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3) {
    // order vertices
    if (v1.x() > v2.x()) {
        Vector vTemp = v1;
        v1 = v2;
        v2 = vTemp;

        Colour cTemp = c1;
        c1 = c2;
        c2 = cTemp;
    }
    if (v2.x() > v3.x()) {
        Vector vTemp = v2;
        v2 = v3;
        v3 = vTemp;

        Colour cTemp = c2;
        c2 = c3;
        c3 = cTemp;
    }
    if (v1.x() > v2.x()) {
        Vector vTemp = v1;
        v1 = v2;
        v2 = vTemp;

        Colour cTemp = c1;
        c1 = c2;
        c2 = cTemp;
    }
    
    // calculate gradients and differences
    const double error = 0.01;
    Vector v1ToV2 = v2-v1, v1ToV3 = v3-v1, v2ToV3 = v3-v2;
    Vector dBydx12 = v1ToV2 / (v1ToV2.x() + error);
    Vector dBydx13 = v1ToV3 / (v1ToV3.x() + error);
    Vector dBydx23 = v2ToV3 / (v2ToV3.x() + error);

    Colour c1ToC2 = c2-c1, c1ToC3 = c3-c1, c2ToC3 = c3-c2;
    double drBydx12 = c1ToC2.r() / (v1ToV2.x() + error);
    double dgBydx12 = c1ToC2.g() / (v1ToV2.x() + error);
    double dbBydx12 = c1ToC2.b() / (v1ToV2.x() + error);
    double daBydx12 = c1ToC2.a() / (v1ToV2.x() + error);

    double drBydx13 = c1ToC3.r() / (v1ToV3.x() + error);
    double dgBydx13 = c1ToC3.g() / (v1ToV3.x() + error);
    double dbBydx13 = c1ToC3.b() / (v1ToV3.x() + error);
    double daBydx13 = c1ToC3.a() / (v1ToV3.x() + error);

    double drBydx23 = c2ToC3.r() / (v2ToV3.x() + error);
    double dgBydx23 = c2ToC3.g() / (v2ToV3.x() + error);
    double dbBydx23 = c2ToC3.b() / (v2ToV3.x() + error);
    double daBydx23 = c2ToC3.a() / (v2ToV3.x() + error);


    // draw the first sub triangle
    for (double x = 0; x < v1ToV2.x(); x++) {
        Vector vertex1 = v1 + Vector(x, dBydx12.y() * x, dBydx12.z() * x, 0);
        Vector vertex2 = v1 + Vector(x, dBydx13.y() * x, dBydx13.z() * x, 0);
        Colour colour1 = c1 + Colour(drBydx12 * x, dgBydx12 * x, dbBydx12 * x, daBydx12 * x);
        Colour colour2 = c1 + Colour(drBydx13 * x, dgBydx13 * x, dbBydx13 * x, daBydx13 * x);
        drawLine(bmap, vertex1, vertex2, colour1, colour2);
    }
    // and the second
    for (double x = 0; x < v2ToV3.x(); x++) {
        double x2 = v1ToV2.x() + x;
        Vector vertex1 = v2 + Vector(x, dBydx23.y() * x, dBydx23.z() * x, 0);
        Vector vertex2 = v1 + Vector(x2, dBydx13.y() * x2, dBydx13.z() * x2, 0);
        Colour colour1 = c2 + Colour(drBydx23 * x, dgBydx23 * x, dbBydx23 * x, daBydx23 * x);
        Colour colour2 = c1 + Colour(drBydx13 * x2, dgBydx13 * x2, dbBydx13 * x2, daBydx13 * x2);
        drawLine(bmap, vertex1, vertex2, colour1, colour2);
    }
}

/**
 * Draws a line onto a given bitmap, defined by the start and end colours and vectors
 * Implemented the DDA (differential analyser) algorithm
 * TODO: could implement bresenhams algorithm instead
 * 
 * @param start     the coordinate of the start of the line
 * @param end       the coodinate of the end of the line
 * @param c1, c2    the colours of the start and end of the line
 */
static void drawLine(Bitmap3D& bmap, Vector start, Vector end, Colour c1, Colour c2) {
    // calculate differences
    int x1 = start.x(), y1 = start.y(), z1 = start.z();
    int x2 = end.x(), y2 = end.y(), z2 = end.z();

    double dx = x2-x1, dy = y2-y1, dz = z2-z1;
    double dr = c2.r()-c1.r(), dg = c2.g()-c1.g(), db = c2.b()-c1.b(), da = c2.a() - c1.a();

    bmap.drawPixel(x1, y1, z1, c1);
    if (std::abs(dx) > std::abs(dy)) {
        if (dx == 0) return;

        // calculate gradients
        double ySlope = dy / dx;
        double zSlope = dz / dx;
        double rSlope = dr / dx;
        double gSlope = dg / dx;
        double bSlope = db / dx;
        double aSlope = da / dx;

        // calculate intercepts
        int yError = (y1   - ySlope * x1);
        int zError = (z1   - zSlope * x1);
        int rError = (c1.r() - rSlope * x1);
        int gError = (c1.g() - gSlope * x1);
        int bError = (c1.b() - bSlope * x1);
        int aError = (c1.a() - aSlope * x1);

        int xStep = dx < 0 ? -1 : 1;

        // draw the line
        while (x1 != x2) {
            x1 += xStep;
            y1   = (ySlope * x1) + yError;
            z1   = (zSlope * x1) + zError;
            c1.r() = (rSlope * x1) + rError;
            c1.g() = (gSlope * x1) + gError;
            c1.b() = (bSlope * x1) + bError;
            c1.a() = (aSlope * x1) + aError;
            bmap.drawPixel(x1, y1, z1, c1);
        }
    }
    else {
        if (dy == 0) return;

        // calculate gradients
        double xSlope = dx / dy;
        double zSlope = dz / dy;
        double rSlope = dr / dy;
        double gSlope = dg / dy;
        double bSlope = db / dy;
        double aSlope = da / dy;

        // calculate intercepts
        int xError = (x1   - xSlope * y1);
        int zError = (z1   - zSlope * y1);
        int rError = (c1.r() - rSlope * y1);
        int gError = (c1.g() - gSlope * y1);
        int bError = (c1.b() - bSlope * y1);
        int aError = (c1.a() - aSlope * y1);

        int yStep = dy < 0 ? -1 : 1;

        // draw the line
        while (y1 != y2) {
            y1 += yStep;
            x1   = (xSlope * y1) + xError;
            z1   = (zSlope * y1) + zError;
            c1.r() = (rSlope * y1) + rError;
            c1.g() = (gSlope * y1) + gError;
            c1.b() = (bSlope * y1) + bError;
            c1.a() = (aSlope * y1) + aError;
            bmap.drawPixel(x1, y1, z1, c1);
        }
    }
}
