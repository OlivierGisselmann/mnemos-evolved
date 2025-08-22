#ifndef COMPONENT_MATERIAL_HPP
#define COMPONENT_MATERIAL_HPP

#include <math/vector.hpp>

namespace mnm::ecs
{
    struct PhongMaterial
    {
        math::Vec3f ambient {1.f};
        math::Vec3f diffuse {1.f};
        math::Vec3f specular {1.f};
        f32 specularStrength {32.f};
    };
}

#endif