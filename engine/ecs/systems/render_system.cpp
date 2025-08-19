#include <ecs/systems/render_system.hpp>

extern mnm::ecs::Coordinator gCoordinator;

namespace mnm::ecs
{
    void RenderSystem::Init()
    {
        mShader = std::make_unique<renderer::opengl::Shader>("../../resources/shaders/test.vert", "../../resources/shaders/test.frag");

        // Load OBJ files for each models
        for(auto& entity : mEntities)
        {
            auto& renderable = gCoordinator.GetComponent<Renderable>(entity);
            auto meshData = parser::ReadOBJ(renderable.modelPath);
            renderable.mesh = new renderer::opengl::Mesh(meshData.vertices, meshData.indices);
        }
    }

    void RenderSystem::Update(f32 deltaTime)
    {
        for(const auto& entity : mEntities)
        {
            const auto& transform = gCoordinator.GetComponent<Transform>(entity);
            const auto& renderable = gCoordinator.GetComponent<Renderable>(entity);

            math::Mat4f model;
            math::Mat4f view;
            math::Mat4f projection;

            // Apply transform
            model = math::Translate(model, transform.position);
            model = math::RotateZ(model, transform.rotation.z);
            model = math::RotateX(model, transform.rotation.x);
            model = math::RotateY(model, transform.rotation.y);
            model = math::Scale(model, transform.scale);

            view = math::LookAt(math::Vec3f{0.f, 0.f, -50.f}, math::Vec3f{0.f, 0.f, 1.f}, math::Vec3f{0.f, 1.f, 0.f});
            projection = math::Perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

            // Set uniforms
            mShader->Use();
            mShader->SetUniform("model", model);
            mShader->SetUniform("view", view);
            mShader->SetUniform("projection", projection);
            
            // Draw call
            renderable.mesh->Draw();
        }
    }
}