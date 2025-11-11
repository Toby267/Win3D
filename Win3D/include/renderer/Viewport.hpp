#pragma once

#include "util/Matrix.hpp"

class Viewport {
private:
    int width, height, depthOfField;

    //assumes the canonical view cube is (-1, -1, -1) to (1, 1, 1)
    Matrix transform = Matrix::translate(width/2.0, height/2.0, depthOfField/2.0) * Matrix::scale(width/2.0, -height/2.0, depthOfField/2.0);

public:
    Viewport(int width, int height, int depthOfField);

    Matrix getTransformation() const;
};
