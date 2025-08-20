#ifndef COMPONENT_CAMERA_HPP
#define COMPONENT_CAMERA_HPP

#include <math/matrix.hpp>

namespace mnm::ecs
{
    struct Camera
    {
        math::Vec3f position;
        math::Mat4f viewMatrix;
        math::Mat4f projectionMatrix;
    };
}

#endif