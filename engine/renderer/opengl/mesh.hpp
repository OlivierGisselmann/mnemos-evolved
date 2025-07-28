#ifndef MESH_HPP
#define MESH_HPP

#include <renderer/opengl/vertex_array.hpp>
#include <renderer/opengl/shader.hpp>

namespace mnm::renderer::opengl
{
    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const Shader& shader);
        ~Mesh();

        void Draw();

    private:
        VertexArray mVAO;
        const Shader& mShader;
    };
}

#endif