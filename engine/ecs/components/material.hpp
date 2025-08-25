#ifndef COMPONENT_MATERIAL_HPP
#define COMPONENT_MATERIAL_HPP

#include <math/vector.hpp>
#include <renderer/opengl/texture.hpp>

namespace mnm::ecs
{
    struct PhongMaterial
    {
        math::Vec3f ambient {1.f};
        math::Vec3f diffuse {1.f};
        math::Vec3f specular {1.f};
        f32 specularStrength {32.f};

        renderer::opengl::Texture albedoMap {"../../resources/textures/texture.bmp"}; //Default texture's location
        renderer::opengl::Texture specularMap {"../../resources/textures/texture.bmp"}; //Default texture's location
    };

    struct PBRMaterial
    {
        math::Vec3f albedo {1.f};
        f32 metallic = 0.f;
        f32 roughness = 0.f;
        f32 ao = 0.f;
    };
}

#endif