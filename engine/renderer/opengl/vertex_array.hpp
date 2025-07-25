#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include <types.hpp>
#include <renderer/opengl/vertex_buffer.hpp>

namespace mnm::renderer::opengl
{
    class VertexArray
    {
    public:
        VertexArray(const std::vector<Vertex>& vertices);
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

    private:
        u32 mID;
        VertexBuffer mVertexBuffer;
    };
}

#endif
