#include <renderer/opengl/opengl_renderer.hpp>

#include <renderer/opengl/mesh.hpp>
#include <renderer/opengl/shader.hpp>
#include <core/parsers/obj_parser.hpp>

namespace mnm::renderer::opengl
{
    void OpenGLRenderer::Initialize()
    {
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderer::BeginFrame(math::Vec2u windowSize)
    {
        // Check for window resize
        static math::Vec2u currentSize{};
        if(currentSize != windowSize)
        {
            currentSize = windowSize;
            glViewport(0, 0, currentSize.x, currentSize.y);
        }

        // Clear buffers
        glClearColor((195.f / 256.f), (223.f / 256.f), (224.f / 256.f), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::DrawFrame(f32 deltaTime)
    {
        
    }

    void OpenGLRenderer::EndFrame()
    {

    }
}
