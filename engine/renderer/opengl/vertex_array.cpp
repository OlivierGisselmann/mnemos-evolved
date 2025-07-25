#include <renderer/opengl/vertex_array.hpp>

namespace mnm::renderer::opengl
{
    VertexArray::VertexArray(const std::vector<Vertex>& vertices)
    : mVertexBuffer(vertices)
    {
        glGenVertexArrays(1, &mID);
        Bind();
        mVertexBuffer.Bind();
        Unbind();
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &mID);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(mID);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
}