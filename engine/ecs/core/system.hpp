#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <ecs/types.hpp>

#include <set>

namespace mnm::ecs
{
    class System
    {
    public:
        std::set<Entity> mEntities;
    };
}

#endif