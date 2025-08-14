#include <renderer/opengl/vertex_array.hpp>

namespace mnm::renderer::opengl
{
    VertexArray::VertexArray(const std::vector<Vertex>& vertices, const std::vector<u32>& indices)
    : mVerticesCount(vertices.size()), mIndicesCount(indices.size())
    {
        glGenVertexArrays(1, &mVAO);
        Bind();

        // Vertex Buffer Object
        glGenBuffers(1, &mVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        // Element Buffer Object
        glGenBuffers(1, &mEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), indices.data(), GL_STATIC_DRAW);

        // Vertex attributes
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
        glDeleteBuffers(1, &mEBO);
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