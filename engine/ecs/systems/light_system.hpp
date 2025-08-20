#ifndef LIGHT_SYSTEM_HPP
#define LIGHT_SYSTEM_HPP

#include <ecs/core/coordinator.hpp>
#include <ecs/components/light.hpp>
#include <renderer/opengl/shader.hpp>

namespace mnm::ecs
{
    class LightSystem : public System
    {
    public:
        void Init(std::shared_ptr<renderer::opengl::Shader> shader);

        void Update();

    private:
        std::shared_ptr<renderer::opengl::Shader> mShader;
    };
}

#endif