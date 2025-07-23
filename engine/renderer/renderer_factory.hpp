#ifndef RENDERER_FACTORY_HPP
#define RENDERER_FACTORY_HPP

#include <renderer/renderer.hpp>
#include <renderer/opengl/opengl_renderer.hpp>

#include <memory>

namespace mnm::renderer
{
    enum class RendererBackend
    {
        OpenGL,
        Vulkan,
        DirectX
    };

    class RendererFactory
    {
    public:
        static std::unique_ptr<IRenderer> Create(RendererBackend backend);
    };
}

#endif
