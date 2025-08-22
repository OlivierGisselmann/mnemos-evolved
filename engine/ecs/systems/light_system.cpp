#include <ecs/systems/light_system.hpp>

extern mnm::ecs::Coordinator gCoordinator;

namespace mnm::ecs
{
    void LightSystem::Init(std::shared_ptr<renderer::opengl::Shader> shader)
    {
        mShader = shader;
    }

    void LightSystem::Update()
    {
        for(const auto& entity : mEntities)
        {
            auto& light = gCoordinator.GetComponent<PointLight>(entity);

            mShader->Use();
            mShader->SetUniform("lightColor", light.color);
            mShader->SetUniform("lightIntensity", light.intensity);
            mShader->SetUniform("lightPosition", light.position);

            mShader->SetUniform("lightConstant", light.constant);
            mShader->SetUniform("lightLinear", light.linear);
            mShader->SetUniform("lightQuadratic", light.quadratic);
        }
    }
}