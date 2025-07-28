#include <renderer/opengl/opengl_renderer.hpp>

#include <renderer/opengl/mesh.hpp>
#include <renderer/opengl/shader.hpp>

namespace mnm::renderer::opengl
{
    const std::vector<mnm::renderer::Vertex> vertices = 
    {
        {{-0.5f, -0.5f, 0.0f}, {0.f, 1.f, 0.f}, {0.f}},
        {{0.5f, -0.5f, 0.0f}, {1.f, 0.f, 0.f}, {0.f}},
        {{0.0f,  0.5f, 0.0f}, {0.f, 0.f, 1.f}, {0.f}},
    };

    void OpenGLRenderer::Initialize()
    {
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderer::BeginFrame()
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::DrawFrame()
    {
        Shader shader("../../resources/shaders/test.vert", "../../resources/shaders/test.frag");
        Mesh mesh(vertices, shader);
        mesh.Draw();
    }

    void OpenGLRenderer::EndFrame()
    {

    }
}
