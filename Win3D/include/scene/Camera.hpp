#pragma once

#include "util/Matrix.hpp"
#include "util/Vector.hpp"

class Camera {
private:
    const double width = 1600, height = 900;
    
    double depthOfField;
    int d = 1;
    
    Matrix projection = Matrix::identity(4);

    Vector position     = Vector(0, 0, 0, 1);
    Vector direction    = Vector(0, 0, 1, 0);
    Vector up           = Vector(0, 1, 0, 0);

public:
    //constructors/destructor
    Camera() {};
    Camera(Vector position, Vector direction, Vector up);

    //getters/setters
    Matrix getProjection() const;
    Matrix getTransformation() const;

    void setDepthOfField(int depthOfField);
};