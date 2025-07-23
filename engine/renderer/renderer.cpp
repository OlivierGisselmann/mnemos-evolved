#include <renderer/renderer.hpp>

namespace mnm::renderer
{
    void InitRenderer()
    {
        glEnable(GL_DEPTH);
    }

    void BeginFrame()
    {
        glClearColor(0.9f, 0.8f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderFrame()
    {

    }

    void EndFrame()
    {

    }
}
