#ifndef ECS_TYPES_HPP
#define ECS_TYPES_HPP

#include <defines.hpp>
#include <types.hpp>

#include <bitset>

namespace mnm::ecs
{
    using Entity = u32;
    const Entity MAX_ENTITIES = 5000;

    using ComponentType = u8;
    const ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;
}

#endif
