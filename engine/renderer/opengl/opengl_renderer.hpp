#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP

#include <renderer/renderer.hpp>

#include <glad/glad.h>

namespace mnm::renderer::opengl
{
    class OpenGLRenderer : public IRenderer
    {
    public:
        void Initialize() override;
        void BeginFrame(math::Vec2u windowSize) override;
        void DrawFrame(f32 deltaTime) override;
        void EndFrame() override;
    };
}

#endif
