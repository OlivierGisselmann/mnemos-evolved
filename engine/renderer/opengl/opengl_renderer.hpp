#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP

#include <renderer/renderer.hpp>

#include <glad/glad.h>

namespace mnm::renderer
{
    class OpenGLRenderer : public IRenderer
    {
    public:
        void BeginFrame() override;
        void DrawFrame() override;
        void EndFrame() override;
    };
}

#endif
