#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <types.hpp>
#include <math/vector.hpp>

namespace mnm::renderer
{
    struct UnlitMaterial
    {
        math::Vec3f albedo;
    };

    struct PhongMaterial
    {
        math::Vec3f ambient = {1.0f, 1.0f, 1.0f};
        math::Vec3f diffuse = {1.0f, 1.0f, 1.0f};
        math::Vec3f specular = {1.0f, 1.0f, 1.0f};
        f32 specularStrength = 32.0f;
    };
}

#endif
