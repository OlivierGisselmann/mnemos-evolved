#include <renderer/opengl/opengl_renderer.hpp>

#include <renderer/opengl/mesh.hpp>
#include <renderer/opengl/shader.hpp>

namespace mnm::renderer::opengl
{
    const std::vector<mnm::renderer::Vertex> vertices = 
    {
        {{-0.5f, -0.5f, -0.5f}, {1.f, 0.f, 0.f}, {0.f, 0.f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.f, 0.f, 0.f}, {1.f, 0.f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.f, 0.f, 0.f}, {1.f, 1.f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.f, 0.f, 0.f}, {1.f, 1.f}},
        {{-0.5f,  0.5f, -0.5f}, {1.f, 0.f, 0.f}, {0.f, 1.f}},
        {{-0.5f, -0.5f, -0.5f}, {1.f, 0.f, 0.f}, {0.f, 0.f}},

        {{-0.5f, -0.5f,  0.5f}, {0.f, 1.f, 0.f}, {0.f, 0.f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.f, 1.f, 0.f}, {1.f, 0.f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.f, 1.f, 0.f}, {1.f, 1.f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.f, 1.f, 0.f}, {1.f, 1.f}},
        {{-0.5f,  0.5f,  0.5f}, {0.f, 1.f, 0.f}, {0.f, 1.f}},
        {{-0.5f, -0.5f,  0.5f}, {0.f, 1.f, 0.f}, {0.f, 0.f}},

        {{-0.5f,  0.5f,  0.5f}, {0.f, 0.f, 1.f}, {1.f, 0.f}},
        {{-0.5f,  0.5f, -0.5f}, {0.f, 0.f, 1.f}, {1.f, 1.f}},
        {{-0.5f, -0.5f, -0.5f}, {0.f, 0.f, 1.f}, {0.f, 1.f}},
        {{-0.5f, -0.5f, -0.5f}, {0.f, 0.f, 1.f}, {0.f, 1.f}},
        {{-0.5f, -0.5f,  0.5f}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-0.5f,  0.5f,  0.5f}, {0.f, 0.f, 1.f}, {1.f, 0.f}},

        {{ 0.5f,  0.5f,  0.5f}, {1.f, 1.f, 0.f}, {1.f, 0.f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.f, 1.f, 0.f}, {1.f, 1.f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.f, 1.f, 0.f}, {0.f, 1.f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.f, 1.f, 0.f}, {0.f, 1.f}},
        {{ 0.5f, -0.5f,  0.5f}, {1.f, 1.f, 0.f}, {0.f, 0.f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.f, 1.f, 0.f}, {1.f, 0.f}},

        {{-0.5f, -0.5f, -0.5f}, {0.f, 1.f, 1.f}, {0.f, 1.f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.f, 1.f, 1.f}, {1.f, 1.f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.f, 1.f, 1.f}, {1.f, 0.f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.f, 1.f, 1.f}, {1.f, 0.f}},
        {{-0.5f, -0.5f,  0.5f}, {0.f, 1.f, 1.f}, {0.f, 0.f}},
        {{-0.5f, -0.5f, -0.5f}, {0.f, 1.f, 1.f}, {0.f, 1.f}},

        {{-0.5f,  0.5f, -0.5f}, {1.f, 1.f, 1.f}, {0.f, 1.f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.f, 1.f, 1.f}, {1.f, 1.f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.f, 1.f, 1.f}, {1.f, 0.f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.f, 1.f, 1.f}, {1.f, 0.f}},
        {{-0.5f,  0.5f,  0.5f}, {1.f, 1.f, 1.f}, {0.f, 0.f}},
        {{-0.5f,  0.5f, -0.5f}, {1.f, 1.f, 1.f}, {0.f, 1.f}}
    };

    math::Mat4f model;
    math::Mat4f view;
    math::Mat4f projection;

    void OpenGLRenderer::Initialize()
    {
        glEnable(GL_DEPTH_TEST);

        projection = math::Perspective(45.0f, (float)(1280.0f) / (float)(720.0f), 0.1f, 100.0f);
        view = math::LookAt(math::Vec3f{0.f, 0.f, -5.f}, math::Vec3f{0.f, 0.f, 1.f}, math::Vec3f{0.f, 1.f, 0.f});
        model = math::Translate(model, {0.f});
    }

    void OpenGLRenderer::BeginFrame()
    {
        glClearColor((195.f / 256.f), (223.f / 256.f), (224.f / 256.f), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::DrawFrame(f32 deltaTime)
    {
        Shader shader("../../resources/shaders/test.vert", "../../resources/shaders/test.frag");
        Mesh mesh(vertices, shader);

        static f32 rot = 0.f;
        rot += deltaTime * 15.f;

        model = math::Rotate(model, rot, {0.5f});

        shader.Use();
        shader.SetUniform("model", model);
        shader.SetUniform("view", view);
        shader.SetUniform("projection", projection);

        mesh.Draw();
    }

    void OpenGLRenderer::EndFrame()
    {

    }
}
