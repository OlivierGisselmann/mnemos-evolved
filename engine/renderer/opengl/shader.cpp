#include <renderer/opengl/shader.hpp>

namespace mnm::renderer::opengl
{
    Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        const std::string vertexContent = file::ReadFile(vertexShaderPath);
        const std::string fragmentContent = file::ReadFile(fragmentShaderPath);
        const char* vertexSource = vertexContent.c_str();
        const char* fragmentSource = fragmentContent.c_str();

        // Vertex shader
        mVertShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(mVertShader, 1, &vertexSource, nullptr);
        glCompileShader(mVertShader);
        CheckCompilation(mVertShader);

        // Fragment shader
        mFragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(mFragShader, 1, &fragmentSource, nullptr);
        glCompileShader(mFragShader);
        CheckCompilation(mFragShader);

        // Shader program
        mProgram = glCreateProgram();
        glAttachShader(mProgram, mVertShader);
        glAttachShader(mProgram, mFragShader);
        glLinkProgram(mProgram);
        glValidateProgram(mProgram);

        glDeleteShader(mVertShader);
        glDeleteShader(mFragShader);
    }

    Shader::~Shader()
    {

    }

    void Shader::CheckCompilation(u32 shaderID)
    {
        int result;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

        if(!result)
        {
            char infoLog[512];
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
            log::Log(log::Level::ERR, log::Channel::RENDERER, "Shader compilation failed: ");
            log::Log(log::Level::ERR, log::Channel::RENDERER, infoLog);
        }
    }

    void Shader::Use() const
    {
        glUseProgram(mProgram);
    }

    template<>
    void Shader::SetUniform(const std::string& location, i32 value)
    {
        glUniform1i(glGetUniformLocation(mProgram, location.c_str()), value);
    }

    template<>
    void Shader::SetUniform(const std::string& location, f32 value)
    {
        glUniform1f(glGetUniformLocation(mProgram, location.c_str()), value);
    }

    template<>
    void Shader::SetUniform(const std::string& location, math::Vec3f value)
    {
        glUniform3f(glGetUniformLocation(mProgram, location.c_str()), value.x, value.y, value.z);
    }
}
