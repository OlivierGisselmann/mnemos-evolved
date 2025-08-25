#include <renderer/opengl/framebuffer.hpp>

namespace mnm::renderer::opengl
{
    Framebuffer::Framebuffer()
    {
        // Create Framebuffer
        glGenFramebuffers(1, &mID);
        glBindFramebuffer(GL_FRAMEBUFFER, mID);

        // Create texture attachment
        glGenTextures(1, &mAttachedTexture);
        glBindTexture(GL_TEXTURE_2D, mAttachedTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Attach texture to Framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mAttachedTexture, 0);

        if(!glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
            log::Log(log::Level::ERR, log::Channel::RENDERER, "Failed to create the framebuffer");
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &mID);
    }

    void Framebuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mID);
    }

    void Framebuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}