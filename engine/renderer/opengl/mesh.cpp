#include <renderer/opengl/mesh.hpp>

namespace mnm::renderer::opengl
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indices)
    : mVAO(vertices, indices), mTexture("../../resources/textures/texture.bmp")
    {
    }

    Mesh::~Mesh()
    {

    }

    void Mesh::Draw()
    {
        mVAO.Bind();
        mTexture.Bind();

        glDrawElements(GL_TRIANGLES, mVAO.GetIndicesCount(), GL_UNSIGNED_INT, 0);
    }
}
