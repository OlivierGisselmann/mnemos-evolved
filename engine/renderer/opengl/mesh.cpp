#include <renderer/opengl/mesh.hpp>

namespace mnm::renderer::opengl
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, const Shader& shader)
    : mVAO(vertices), mShader(shader)
    {

    }

    Mesh::~Mesh()
    {

    }

    void Mesh::Draw()
    {
        mVAO.Bind();
        mShader.Use();
        glDrawArrays(GL_TRIANGLES, 0, mVAO.GetVerticesCount());
    }
}
