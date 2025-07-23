#ifndef RENDERER_HPP
#define RENDERER_HPP

namespace mnm::renderer
{
    class IRenderer
    {
    public:
        virtual void Initialize() = 0;
        virtual void BeginFrame() = 0;
        virtual void DrawFrame() = 0;
        virtual void EndFrame() = 0;

        virtual ~IRenderer() = default;
    };
}

#endif
