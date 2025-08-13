#include <renderer/opengl/texture.hpp>

namespace mnm::renderer::opengl
{
    Texture::Texture(const std::string& path)
    {
        glGenTextures(1, &mID);
        glBindTexture(GL_TEXTURE_2D, mID);

        // Set filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        parser::ImageData data = parser::ReadBMP(path);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.pixels.data());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture::~Texture() {}

    u32 Texture::GetID() const
    {
        return mID;
    }

    void Texture::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, mID);
    }
}