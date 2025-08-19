#ifndef COMPONENT_TRANSFORM_HPP
#define COMPONENT_TRANSFORM_HPP

#include <math/vector.hpp>

namespace mnm::ecs
{
    struct Transform
    {
        math::Vec3f position{0.0f};
        math::Vec3f rotation{0.0f};
        math::Vec3f scale{1.0f};
    };
}

#endif