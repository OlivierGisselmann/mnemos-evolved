#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include <types.hpp>
#include <renderer/structs/vertex.hpp>

#include <glad/glad.h>
#include <vector>

namespace mnm::renderer::opengl
{
    class VertexArray
    {
    public:
        VertexArray(const std::vector<Vertex>& vertices);
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        u32 GetVerticesCount() const;
        u32 GetIndicesCount() const;

    private:
        u32 mVAO{}, mVBO{};

        u32 mVerticesCount{};
        u32 mIndicesCount{};
    };
}

#endif
