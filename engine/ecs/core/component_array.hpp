#ifndef COMPONENT_ARRAY_HPP
#define COMPONENT_ARRAY_HPP

#include <types.hpp>
#include <ecs/types.hpp>

#include <array>
#include <cassert>
#include <unordered_map>

namespace mnm::ecs
{
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        void InsertData(Entity entity, T component)
        {
            assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Can't add a component multiple times to the same entity");

            sizet newIndex = mSize;
            mEntityToIndexMap[entity] = newIndex;
            mIndexToEntityMap[newIndex] = entity;
            mComponentArray[newIndex] = component;
            ++mSize;
        }

        void RemoveData(Entity entity)
        {
            assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component");

            // Move last element to recently deleted element's position
            sizet indexOfRemovedEntity = mEntityToIndexMap[entity];
            sizet indexOfLastElement = mSize - 1;
            mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

            Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
            mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            mEntityToIndexMap.erase(entity);
            mIndexToEntityMap.erase(indexOfLastElement);

            --mSize;
        }

        T& GetData(Entity entity)
        {
            assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component");

            return mComponentArray[mEntityToIndexMap[entity]];
        }

        void EntityDestroyed(Entity entity) override
        {
            if(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
                RemoveData(entity);
        }

    private:
        std::array<T, MAX_ENTITIES> mComponentArray{};
        std::unordered_map<Entity, sizet> mEntityToIndexMap{};
        std::unordered_map<sizet, Entity> mIndexToEntityMap{};
        sizet mSize{};
    };
}

#endif