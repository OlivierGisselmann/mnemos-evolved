#ifndef SHADER_HPP
#define SHADER_HPP

#include <types.hpp>
#include <core/filesystem/filesystem.hpp>
#include <math/matrix.hpp>

#include <glad/glad.h>
#include <string>
#include <unordered_map>

namespace mnm::renderer::opengl
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShader, const std::string& fragmentShader);
        ~Shader();

        void Use() const;

        template <typename T>
        void SetUniform(const std::string& location, T value);

    private:
        void CheckCompilation(u32 shaderID);
        i32 GetUniformLocation(const std::string& location);

        u32 mProgram, mVertShader, mFragShader;
        std::unordered_map<std::string, u32> mLocationCache;
    };
}

#endif
