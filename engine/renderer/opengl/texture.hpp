#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <types.hpp>
#include <core/parsers/bmp_parser.hpp>

#include <glad/glad.h>
#include <string>

namespace mnm::renderer::opengl
{
    class Texture
    {
    public:
        Texture(const std::string& path);
        ~Texture();

        void Bind() const;

        u32 GetID() const;

    private:
        u32 mID;
    };
}

#endif