#include <renderer/renderer_factory.hpp>

namespace mnm::renderer
{
    std::unique_ptr<IRenderer> CreateRenderer(RendererBackend backend)
    {
        switch (backend)
        {
        case RendererBackend::OpenGL:
        {
            return std::make_unique<opengl::OpenGLRenderer>();
        }
        case RendererBackend::Vulkan:
        {
            return std::make_unique<opengl::OpenGLRenderer>(); // Temporary
        }
        case RendererBackend::DirectX:
        {
            return std::make_unique<opengl::OpenGLRenderer>(); // Temporary
        }
        default:
        {
            return std::make_unique<opengl::OpenGLRenderer>(); // Temporary
        }
        }
    }
}
