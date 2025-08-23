#ifndef MESH_HPP
#define MESH_HPP

#include <renderer/opengl/vertex_array.hpp>

namespace mnm::renderer::opengl
{
    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indices);
        ~Mesh();

        void Draw();

    private:
        VertexArray mVAO;
    };
}

#endif