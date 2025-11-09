#include "scene/Camera.hpp"

Camera::Camera() { }

Matrix Camera::getProjection() {
    return projection;
}