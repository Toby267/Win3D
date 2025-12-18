#include "graphicsPipeline/RayTracer.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

#include "util/Vector.hpp"
#include "util/Colour.hpp"

static void orderTrianglesAntiClockwise(Vector& v1, Vector& v2, Vector& v3);

RayTracer::RayTracer(Bitmap3D& bmap)
    : bitmap(bmap)
{
    
}

void RayTracer::trace(std::vector<Object3D>& objects) {
    //these are defined in the camera
    const int cameraWidth = 1280;
    const int cameraHeight = 720;
    int focalDistance = 1000;

    int x = cameraWidth/2, y = cameraHeight/2;

    std::vector<Ray> rays = std::vector<Ray>(cameraHeight*cameraHeight);

    //loop through each pixel of the window
    for (int i = -cameraWidth/2; i < cameraWidth/2; i++) {
        for (int j = -cameraHeight/2; j < cameraHeight/2; j++) {
            Vector origin = Vector(0, 0, 0, 1);
            Vector direction = Vector(i, j, focalDistance, 0).normalise();
            Vector coord = Vector(i+x, cameraHeight-(j+y));
            Colour col = Colour::blue();

            rays.emplace_back(origin, direction, coord, col);
        }
    }

    for (Ray& ray : rays) {
        for (Object3D& obj : objects) {
            std::vector<Vector> vertices = obj.getVertices();
            std::vector<Colour> colours = obj.getColours();

            for (Vector t : obj.getTriangles()) {
                float d = mollerTrumboreIntersection(ray.origin, ray.direction, vertices[t[0]], vertices[t[1]], vertices[t[2]]);
                if (d != -1) { bitmap.drawPixel(ray.screenCoord.x(), ray.screenCoord.y(), 1000, ray.col);}
            }
        }
    }
}

float RayTracer::mollerTrumboreIntersection(Vector orig, Vector dir, Vector vert0, Vector vert1, Vector vert2) {
    constexpr float epsilon = std::numeric_limits<float>::epsilon();

    Vector edge1 = vert1 - vert0;
    Vector edge2 = vert2 - vert0;

    Vector pvec = Vector::crossProduct(dir, edge2);
    float det = Vector::dotProduct(edge1, pvec);

    if (det > -epsilon && det < epsilon)
        return -1;

    float invDet = 1.0 / det;

    Vector tvec = orig - vert0;
    float u = Vector::dotProduct(tvec, pvec) * invDet;

    if (u < 0.0 || u > 1.0)
        return -1;

    Vector qvec = Vector::crossProduct(tvec, edge1);
    float v = Vector::dotProduct(dir, qvec) * invDet;

    if ( v < 0.0 || u + v > 1.0)
        return -1;

    float t = Vector::dotProduct(edge2, qvec) * invDet;
    return t;
}