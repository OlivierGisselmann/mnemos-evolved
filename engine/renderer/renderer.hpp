#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>

namespace mnm::renderer
{
    void InitRenderer();
    void BeginFrame();
    void RenderFrame();
    void EndFrame();
}

#endif
