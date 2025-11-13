#include "graphicsPipelineOop/RasterizerClass.hpp"


void RasterizerClass::rasterize(std::vector<Object3D>& objects, Bitmap3D& bmap) {
    for (Object3D obj : objects) {
        std::vector<Vector> vertices = obj.getVertices();
        std::vector<Colour> colours = obj.getColours();
    
        for (Vector t : obj.getTriangles()) {
            this->drawTriangle(bmap, vertices[t[0]], vertices[t[1]], vertices[t[2]], colours[t[0]], colours[t[1]], colours[t[2]]);
        }
    }
}
    
void RasterizerClass::drawTriangle(Bitmap3D& bmap, Vector v1, Vector v2, Vector v3, Colour c1, Colour c2, Colour c3) {
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
    
    const double error = 0.01;
    Vector v1ToV2 = v2-v1, v1ToV3 = v3-v1, v2ToV3 = v3-v2;
    Vector dBydx12 = v1ToV2 / (v1ToV2.x() + error);
    Vector dBydx13 = v1ToV3 / (v1ToV3.x() + error);
    Vector dBydx23 = v2ToV3 / (v2ToV3.x() + error);

    Colour c1ToC2 = c2-c1, c1ToC3 = c3-c1, c2ToC3 = c3-c2;
    double drBydx12 = c1ToC2.r / (v1ToV2.x() + error);
    double dgBydx12 = c1ToC2.g / (v1ToV2.x() + error);
    double dbBydx12 = c1ToC2.b / (v1ToV2.x() + error);
    double daBydx12 = c1ToC2.a / (v1ToV2.x() + error);

    double drBydx13 = c1ToC3.r / (v1ToV3.x() + error);
    double dgBydx13 = c1ToC3.g / (v1ToV3.x() + error);
    double dbBydx13 = c1ToC3.b / (v1ToV3.x() + error);
    double daBydx13 = c1ToC3.a / (v1ToV3.x() + error);

    double drBydx23 = c2ToC3.r / (v2ToV3.x() + error);
    double dgBydx23 = c2ToC3.g / (v2ToV3.x() + error);
    double dbBydx23 = c2ToC3.b / (v2ToV3.x() + error);
    double daBydx23 = c2ToC3.a / (v2ToV3.x() + error);


    for (double x = 0; x < v1ToV2.x(); x++) {
        Vector vertex1 = v1 + Vector(x, dBydx12.y() * x, dBydx12.z() * x, 0);
        Vector vertex2 = v1 + Vector(x, dBydx13.y() * x, dBydx13.z() * x, 0);
        Colour colour1 = c1 + Colour(drBydx12 * x, dgBydx12 * x, dbBydx12 * x, daBydx12 * x);
        Colour colour2 = c1 + Colour(drBydx13 * x, dgBydx13 * x, dbBydx13 * x, daBydx13 * x);
        this->drawLine(bmap, vertex1, vertex2, colour1, colour2);
    }
    for (double x = 0; x < v2ToV3.x(); x++) {
        double x2 = v1ToV2.x() + x;
        Vector vertex1 = v2 + Vector(x, dBydx23.y() * x, dBydx23.z() * x, 0);
        Vector vertex2 = v1 + Vector(x2, dBydx13.y() * x2, dBydx13.z() * x2, 0);
        Colour colour1 = c2 + Colour(drBydx23 * x, dgBydx23 * x, dbBydx23 * x, daBydx23 * x);
        Colour colour2 = c1 + Colour(drBydx13 * x2, dgBydx13 * x2, dbBydx13 * x2, daBydx13 * x2);
        this->drawLine(bmap, vertex1, vertex2, colour1, colour2);
    }
}
void RasterizerClass::drawLine(Bitmap3D& bmap, Vector start, Vector end, Colour c1, Colour c2) {
    int x1 = start.x(), y1 = start.y(), z1 = start.z();
    int x2 = end.x(), y2 = end.y(), z2 = end.z();

    double dx = x2-x1, dy = y2-y1, dz = z2-z1;
    double dr = c2.r-c1.r, dg = c2.g-c1.g, db = c2.b-c1.b, da = c2.a - c1.a;

    bmap.drawPixel(x1, y1, z1, c1);
    if (std::abs(dx) > std::abs(dy)) {
        if (dx == 0) return;

        double ySlope = dy / dx;
        double zSlope = dz / dx;
        double rSlope = dr / dx;
        double gSlope = dg / dx;
        double bSlope = db / dx;
        double aSlope = da / dx;

        int yError = (y1   - ySlope * x1);
        int zError = (z1   - zSlope * x1);
        int rError = (c1.r - rSlope * x1);
        int gError = (c1.g - gSlope * x1);
        int bError = (c1.b - bSlope * x1);
        int aError = (c1.a - aSlope * x1);

        int xStep = dx < 0 ? -1 : 1;

        while (x1 != x2) {
            x1 += xStep;
            y1   = (ySlope * x1) + yError;
            z1   = (zSlope * x1) + zError;
            c1.r = (rSlope * x1) + rError;
            c1.g = (gSlope * x1) + gError;
            c1.b = (bSlope * x1) + bError;
            c1.a = (aSlope * x1) + aError;
            bmap.drawPixel(x1, y1, z1, c1);
        }
    }
    else {
        if (dy == 0) return;

        double xSlope = dx / dy;
        double zSlope = dz / dy;
        double rSlope = dr / dy;
        double gSlope = dg / dy;
        double bSlope = db / dy;
        double aSlope = da / dy;

        int xError = (x1   - xSlope * y1);
        int zError = (z1   - zSlope * y1);
        int rError = (c1.r - rSlope * y1);
        int gError = (c1.g - gSlope * y1);
        int bError = (c1.b - bSlope * y1);
        int aError = (c1.a - aSlope * y1);

        int yStep = dy < 0 ? -1 : 1;

        while (y1 != y2) {
            y1 += yStep;
            x1   = (xSlope * y1) + xError;
            z1   = (zSlope * y1) + zError;
            c1.r = (rSlope * y1) + rError;
            c1.g = (gSlope * y1) + gError;
            c1.b = (bSlope * y1) + bError;
            c1.a = (aSlope * y1) + aError;
            bmap.drawPixel(x1, y1, z1, c1);
        }
    }
}