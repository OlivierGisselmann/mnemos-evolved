#ifndef CAMERA_COMPONENT_HPP
#define CAMERA_COMPONENT_HPP

#include <math/matrix.hpp>

namespace mnm::ecs
{
    struct Camera
    {
        math::Mat4f viewMatrix;
        math::Mat4f projectionMatrix;
    };
}

#endif