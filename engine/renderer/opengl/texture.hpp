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
        Texture(const std::string& path = "");
        ~Texture();

        void Bind(u32 slot = 0) const;

    private:
        u32 mID;
    };
}

#endif