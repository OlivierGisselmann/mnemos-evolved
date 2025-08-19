#ifndef COMPONENT_RENDERABLE_HPP
#define COMPONENT_RENDERABLE_HPP

#include <renderer/opengl/mesh.hpp>

#include <memory>
#include <string>

namespace mnm::ecs
{
    struct Renderable
    {
        std::string modelPath{};
        std::shared_ptr<renderer::opengl::Mesh> mesh{nullptr};
    };
}

#endif