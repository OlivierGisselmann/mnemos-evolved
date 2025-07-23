#ifndef RENDERER_FACTORY_HPP
#define RENDERER_FACTORY_HPP

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

    std::unique_ptr<IRenderer> CreateRenderer(RendererBackend backend);
}

#endif
