#include "renderer/Viewport.hpp"

Viewport::Viewport(int width, int height, int depthOfField) :
    width(width), height(height), depthOfField(depthOfField)
{

}

Matrix Viewport::getTransformation() const {
    return transform;
}