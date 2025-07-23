#include <renderer/renderer_factory.hpp>

namespace mnm::renderer
{
    std::unique_ptr<IRenderer> RendererFactory::Create(RendererBackend backend)
    {
        switch (backend)
        {
        case OpenGL:
        {
            return std::make_unique<OpenGLRenderer>();
        }
        case Vulkan:
        {
            return std::make_unique<OpenGLRenderer>(); // Temporary
        }
        case DirectX:
        {
            return std::make_unique<OpenGLRenderer>(); // Temporary
        }
        default:
        {
            return std::make_unique<OpenGLRenderer>(); // Temporary
        }
        }
    }
}
