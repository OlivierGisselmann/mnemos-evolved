#include <ecs/systems/camera_system.hpp>

extern mnm::ecs::Coordinator gCoordinator;

namespace mnm::ecs
{
    void CameraSystem::Init(std::shared_ptr<renderer::opengl::Shader> shader)
    {
        mShader = shader;
    }

    void CameraSystem::Update(f32 deltaTime, math::Vec2u windowSize)
    {
        for(const auto& entity : mEntities)
        {
            auto& camera = gCoordinator.GetComponent<Camera>(entity);

            camera.projectionMatrix = math::Perspective(45.0f, (float)windowSize.x / (float)windowSize.y, 0.1f, 100.0f);
            camera.viewMatrix = math::LookAt(camera.position, math::Vec3f{0.f, 0.f, 0.f}, math::Vec3f{0.f, 1.f, 0.f});

            mShader->Use();
            mShader->SetUniform("view", camera.viewMatrix);
            mShader->SetUniform("projection", camera.projectionMatrix);
            mShader->SetUniform("viewPosition", camera.position);
        }
    }
}