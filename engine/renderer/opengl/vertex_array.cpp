#include <renderer/opengl/vertex_array.hpp>

namespace mnm::renderer::opengl
{
    VertexArray::VertexArray(const std::vector<Vertex>& vertices)
    : mVerticesCount(vertices.size())
    {
        glGenVertexArrays(1, &mVAO);
        Bind();

        glGenBuffers(1, &mVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
        glEnableVertexAttribArray(2);

        Unbind();
    }

    VertexArray::~VertexArray()
    {
        glDeleteBuffers(1, &mVBO);
        glDeleteVertexArrays(1, &mVAO);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(mVAO);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    u32 VertexArray::GetIndicesCount() const
    {
        return mIndicesCount;
    }

    u32 VertexArray::GetVerticesCount() const
    {
        return mVerticesCount;
    }
}