#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <types.hpp>
#include <math/vector.hpp>

namespace mnm::renderer
{
    class IRenderer
    {
    public:
        virtual void Initialize() = 0;
        virtual void BeginFrame(math::Vec2u windowSize) = 0;
        virtual void DrawFrame(f32 deltaTime) = 0;
        virtual void EndFrame() = 0;

        virtual ~IRenderer() = default;
    };
}

#endif
