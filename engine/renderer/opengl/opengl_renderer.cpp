#include <renderer/opengl/opengl_renderer.hpp>

#include <renderer/opengl/mesh.hpp>
#include <renderer/opengl/shader.hpp>
#include <core/parsers/obj_parser.hpp>

namespace mnm::renderer::opengl
{
    math::Mat4f model;
    math::Mat4f view;
    math::Mat4f projection;

    Shader* shader = nullptr;
    Mesh* mesh = nullptr;

    void OpenGLRenderer::Initialize()
    {
        glEnable(GL_DEPTH_TEST);

        shader = new Shader("../../resources/shaders/test.vert", "../../resources/shaders/test.frag");

        parser::MeshData meshData = parser::ReadOBJ("../../resources/models/teapot.obj");
        mesh = new Mesh(meshData.vertices, meshData.indices);

        LOG(std::format("Mesh has {} vertices and {} indices", meshData.vertices.size(), meshData.indices.size()));

        view = math::LookAt(math::Vec3f{0.f, 0.f, -5.f}, math::Vec3f{0.f, 0.f, 1.f}, math::Vec3f{0.f, 1.f, 0.f});
        model = math::Translate(model, {0.f, -1.f, -5.f});
        model = math::Scale(model, {0.7f});
    }

    void OpenGLRenderer::BeginFrame(math::Vec2u windowSize)
    {
        // Check for window resize
        static math::Vec2u currentSize{};
        if(currentSize != windowSize)
        {
            currentSize = windowSize;
            glViewport(0, 0, currentSize.x, currentSize.y);
            projection = math::Perspective(45.0f, (f32)(currentSize.x) / (f32)(currentSize.y), 0.1f, 100.0f);
        }

        // Clear buffers
        glClearColor((195.f / 256.f), (223.f / 256.f), (224.f / 256.f), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::DrawFrame(f32 deltaTime)
    {
        static f32 rot = 0.f;
        rot = deltaTime * 15.f;

        model = math::Rotate(model, rot, {0.f, 1.f, 0.f});

        shader->Use();
        shader->SetUniform("model", model);
        shader->SetUniform("view", view);
        shader->SetUniform("projection", projection);

        mesh->Draw();
    }

    void OpenGLRenderer::EndFrame()
    {

    }
}
