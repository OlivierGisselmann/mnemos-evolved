#include <renderer/opengl/opengl_renderer.hpp>

namespace mnm::renderer
{
    void OpenGLRenderer::BeginFrame()
    {
        glClearColor(0.5f, 0.3f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRenderer::DrawFrame()
    {
        
    }

    void OpenGLRenderer::EndFrame()
    {
        
    }
}
