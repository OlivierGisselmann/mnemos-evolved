#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <types.hpp>
#include <core/logging/log.hpp>

#include <glad/glad.h>

namespace mnm::renderer::opengl
{
    class Framebuffer
    {
    public:
        Framebuffer();
        ~Framebuffer();

        void Bind() const;
        void Unbind() const;
        
    private:
        u32 mID;
        u32 mAttachedTexture;
    };
}

#endif