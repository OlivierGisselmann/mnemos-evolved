#ifndef CAMERA_SYSTEM_HPP
#define CAMERA_SYSTEM_HPP

#include <ecs/core/coordinator.hpp>
#include <ecs/components/camera.hpp>
#include <renderer/opengl/shader.hpp>

namespace mnm::ecs
{
    class CameraSystem : public System
    {
    public:
        void Init(std::shared_ptr<renderer::opengl::Shader> shader);

        void Update(f32 deltaTime, math::Vec2u windowSize);

    private:
        std::shared_ptr<renderer::opengl::Shader> mShader;
    };
}

#endif