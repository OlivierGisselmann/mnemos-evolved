#ifndef MESH_HPP
#define MESH_HPP

#include <renderer/opengl/vertex_array.hpp>
#include <renderer/opengl/shader.hpp>
#include <renderer/opengl/texture.hpp>
#include <renderer/structs/material.hpp>

namespace mnm::renderer::opengl
{
    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, Shader& shader);
        ~Mesh();

        void Draw();

    private:
        VertexArray mVAO;
        Shader& mShader;
        PhongMaterial mMaterial;
        Texture mTexture;
    };
}

#endif