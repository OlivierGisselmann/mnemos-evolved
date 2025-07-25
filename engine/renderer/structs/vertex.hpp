#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <math/vector.hpp>

namespace mnm::renderer
{
    struct Vertex
    {
        math::Vec3f position;
        math::Vec3f normal;
        math::Vec2f texCoords;
    };
}

#endif