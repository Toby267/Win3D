#pragma once

#include "util/Matrix.hpp"
#include "util/Vector.hpp"

class Camera {
private:
    const double width = 1600, height = 900;
    double depthOfField;
    
    Matrix projection = Matrix::identity(4);

    Vector position     = Vector(0, 0, 0, 1);
    Vector direction    = Vector(0, 0, 1, 0);
    Vector up           = Vector(0, 1, 0, 0);

    int d = 1;

public:
    //constructors/destructor
    Camera() {};

    //getters/setters
    Matrix getProjection() const;
    Matrix getTransformation() const;

    void setDepthOfField(int depthOfField);
};