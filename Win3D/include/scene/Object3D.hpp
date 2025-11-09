#pragma once

#include <vector>

#include "Camera.hpp"
#include "renderer/Bitmap3D.hpp"

#include "util/Matrix.hpp"
#include "util/Vector.hpp"
#include "util/Colour.hpp"

/**
 * stores the data of an object. the vertices is just a list of vectors, one per vertex. colours[i] is the colour of vertices[i].
 * triangles[i] stores the first tirangle, where triangle[i][0] is v1, triangle[i][1] is v2, and triangle[i][2] is v3.
 * we'll get to uv maps later
 */
struct Object3D {
    std::vector<Vector> vertices;
    std::vector<Colour> colours;
    std::vector<Vector> triangles;
    std::vector<Vector> uvCoordinates;

    Matrix scale       = Matrix::scale(1, 1, 1);
    Matrix translation = Matrix::translate(0, 0, 0);
    Matrix rotation    = Matrix::rotation(0, 0, 0);

    Matrix affineTransform = translation * scale * rotation;

    Camera* cameraRef;

public:
    //constructors/destructor
    Object3D(std::vector<Vector> vertices, std::vector<Colour> colours, std::vector<Vector> triangles);

    //getters/setters
    void setScale(Matrix s);
    void setTranslation(Matrix t);
    void setRotation(Matrix r);

    void setCamera(Camera* camera);

    //public methods
    void transform();
    void project();
    void applyViewportTransformation(Matrix transformationMatrix);
    void draw(Bitmap3D& bmap);

    //static methods
    static Object3D cube();
};