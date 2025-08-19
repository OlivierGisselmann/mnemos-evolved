#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <core/parsers/obj_parser.hpp>
#include <ecs/core/coordinator.hpp>
#include <ecs/components/renderable.hpp>
#include <ecs/components/transform.hpp>
#include <renderer/opengl/shader.hpp>
#include <renderer/opengl/mesh.hpp>

namespace mnm::ecs
{
    class RenderSystem : public System
    {
    public:
        void Init();

        void Update(f32 deltaTime);

    private:
        std::unique_ptr<renderer::opengl::Shader> mShader;
        std::unique_ptr<renderer::opengl::Mesh> mMesh;
    };
}

#endif