#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <types.hpp>
#include <renderer/structs/vertex.hpp>

#include <glad/glad.h>
#include <vector>

namespace mnm::renderer::opengl
{
    class VertexBuffer
    {
    public:
        VertexBuffer(const std::vector<Vertex>& vertices);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

    private:
        u32 mID;
    };
}

#endif
