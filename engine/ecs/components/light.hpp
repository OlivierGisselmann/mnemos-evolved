#ifndef COMPONENT_LIGHT_HPP
#define COMPONENT_LIGHT_HPP

#include <math/vector.hpp>

namespace mnm::ecs
{
    struct DirectionalLight
    {
        math::Vec3f direction;
        math::Vec3f color {1.f, 1.f, 1.f};
        f32 intensity = 1.f;
    };

    struct PointLight
    {
        math::Vec3f position;
        math::Vec3f color = {1.f, 1.f, 1.f};
        f32 intensity = 1.f;

        f32 constant = 1.0f;
        f32 linear = 0.09f;
        f32 quadratic = 0.032f;
    };
}

#endif