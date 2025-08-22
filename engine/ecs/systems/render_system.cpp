#include <ecs/systems/render_system.hpp>

extern mnm::ecs::Coordinator gCoordinator;

namespace mnm::ecs
{
    void RenderSystem::Init(std::shared_ptr<renderer::opengl::Shader> shader)
    {
        mShader = shader;

        // Create mesh for each entity
        for(auto& entity : mEntities)
        {
            auto& renderable = gCoordinator.GetComponent<Renderable>(entity);
            auto meshData = parser::ReadOBJ(renderable.modelPath);
            renderable.mesh = std::make_shared<renderer::opengl::Mesh>(meshData->vertices, meshData->indices);
        }
    }

    void RenderSystem::Update(f32 deltaTime)
    {
        for(const auto& entity : mEntities)
        {
            // Get entity's components
            const auto& transform = gCoordinator.GetComponent<Transform>(entity);
            const auto& renderable = gCoordinator.GetComponent<Renderable>(entity);
            const auto& material = gCoordinator.GetComponent<PhongMaterial>(entity);

            math::Mat4f model;

            // Apply transform
            model = math::Translate(model, transform.position);
            model = math::RotateZ(model, transform.rotation.z);
            model = math::RotateX(model, transform.rotation.x);
            model = math::RotateY(model, transform.rotation.y);
            model = math::Scale(model, transform.scale);

            // Set uniforms
            mShader->Use();
            mShader->SetUniform("model", model);

            mShader->SetUniform("ambientColor", material.ambient);
            mShader->SetUniform("diffuseColor", material.diffuse);
            mShader->SetUniform("specularColor", material.specular);
            mShader->SetUniform("specularStrength", material.specularStrength);
            
            // Draw call
            renderable.mesh->Draw();
        }
    }
}