#include "graphicsPipeline/RayTracer.hpp"

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
        // Vector v3(-100, -100, 1500), v1(100, 100, 1500), v2(100, -100, 1500);
        // orderTrianglesAntiClockwise(v1, v2, v3);
        // float t = mollerTrumboreIntersection(ray.origin, ray.direction, v1, v2, v3);
        // if (t != -1) bitmap.drawPixel(ray.screenCoord[0], ray.screenCoord[1], 1000, ray.col);
        // continue;

        for (Object3D& obj : objects) {
            std::vector<Vector> vertices = obj.getVertices();
            std::vector<Colour> colours = obj.getColours();
            // std::vector<Vector> triangles = obj.getTriangles();
            // Vector t = triangles[4];
        
            for (Vector t : obj.getTriangles()) {
                orderTrianglesAntiClockwise(vertices[t[0]], vertices[t[1]], vertices[t[2]]);
                float d = mollerTrumboreIntersection(ray.origin, ray.direction, vertices[t[0]], vertices[t[1]], vertices[t[2]]);
                if (d != -1) { bitmap.drawPixel(ray.screenCoord.x(), ray.screenCoord.y(), 1000, ray.col);}
            }
        }
    }
}

void orderTrianglesAntiClockwise(Vector& v1, Vector& v2, Vector& v3) {
    if (v1.x() > v2.x()) {
        Vector vTemp = v1;
        v1 = v2;
        v2 = vTemp;

        // Colour cTemp = c1;
        // c1 = c2;
        // c2 = cTemp;
    }
    if (v2.x() > v3.x()) {
        Vector vTemp = v2;
        v2 = v3;
        v3 = vTemp;

        // Colour cTemp = c2;
        // c2 = c3;
        // c3 = cTemp;
    }
    if (v1.x() > v2.x()) {
        Vector vTemp = v1;
        v1 = v2;
        v2 = vTemp;

        // Colour cTemp = c1;
        // c1 = c2;
        // c2 = cTemp;
    }
    if (v2.y() < v3.y()) {
        Vector vTemp = v2;
        v2 = v3;
        v3 = vTemp;

        // Colour cTemp = c1;
        // c1 = c2;
        // c2 = cTemp;
    }
}


float RayTracer::barycentricIntersection() {

}

float RayTracer::waldMethodIntersection() {

}

#define TEST_CULL
//returns t - the distance
float RayTracer::mollerTrumboreIntersection(Vector orig, Vector dir, Vector vert0, Vector vert1, Vector vert2) {
    // std::cout << "hello\n";
    Vector edge1, edge2, tvec, pvec, qvec;
    double det, inv_det;

    //find vectors for the two edges sharing vert0
    edge1 = vert1 - vert0;
    edge2 = vert2 - vert0;
    // std::cout << "check\n";

    //begin calculating determinant - also used to calculate U parameter
    pvec = Vector::crossProduct(dir, edge2);

    // std::cout << "check\n";

    //if determinant is near zero, ray lies in plane of triangle
    det = Vector::dotProduct(edge1, pvec);

    // std::cout << "check\n";

    //for now, only implement the culling branch, if I need two faced triangles, implement the other branch later
#ifdef TEST_CULL
    if (det < std::numeric_limits<float>::epsilon()) {
        // std::cout << "returning\n";
        return -1;
    }

    //calculate distance from vert0 to ray origin
    tvec = orig - vert0;

    //calculate u parameter and test bounds
    double u = Vector::dotProduct(tvec, pvec);
    if (u < 0 || u > det) {
        // std::cout << "returning\n";
        return -1;
    }

    //prepare to test v parameter
    qvec = Vector::crossProduct(tvec, edge1);

    //calculate v parameter and test bounds
    double v = Vector::dotProduct(dir, qvec);
    if (v < 0 || u + v > det) {
        // std::cout << "returning\n";
        return -1;
    }

    //calculate t, scale parameters, ray intersects triangle
    double t = Vector::dotProduct(edge2, qvec);
    inv_det = 1.0 / det;
    t *= inv_det;

    // std::cout << "returning\n";
    return t;
#else
    if (det > -std::numeric_limits<float>::epsilon() && det < std::numeric_limits<float>::epsilon())
        return -1;

    inv_det = 1.0 / det;

    tvec = orig - vert0;

    double u = Vector::dotProduct(tvec, pvec) * inv_det;
    if ( u < 0 || u > 1)
        return 0;

    qvec = Vector::crossProduct(tvec, edge1);

    double v = Vector::dotProduct(dir, qvec) * inv_det;
    if (v < 0 || u + v > 1)
        return 0;

    double t = Vector::dotProduct(edge2, qvec) * inv_det;
    return t;
#endif
}