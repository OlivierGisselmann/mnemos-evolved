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
        math::Vec3f ambient;
        math::Vec3f diffuse;
        math::Vec3f specular;
        f32 specularStrength;
    };
}

#endif
