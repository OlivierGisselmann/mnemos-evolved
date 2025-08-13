#include <renderer/opengl/mesh.hpp>

namespace mnm::renderer::opengl
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, Shader& shader)
    : mVAO(vertices), mShader(shader)
    {
        mMaterial.ambient = math::Vec3f(0.2f, 0.2f, 0.2f);
        mMaterial.diffuse = math::Vec3f(0.f, 1.f, 0.f);
        mMaterial.specular = math::Vec3f(1.0f, 0.f, 0.f);
        mMaterial.specularStrength = 256.0f;
    }

    Mesh::~Mesh()
    {

    }

    void Mesh::Draw()
    {
        mVAO.Bind();
        mShader.Use();

        mShader.SetUniform("ambient", mMaterial.ambient);
        mShader.SetUniform("diffuse", mMaterial.diffuse);
        mShader.SetUniform("specular", mMaterial.specular);
        mShader.SetUniform("specularStrength", mMaterial.specularStrength);

        glDrawArrays(GL_TRIANGLES, 0, mVAO.GetVerticesCount());
    }
}
