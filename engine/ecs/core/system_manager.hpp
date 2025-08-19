#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include <types.hpp>
#include <ecs/types.hpp>
#include <ecs/core/system.hpp>

#include <cassert>
#include <memory>
#include <unordered_map>

namespace mnm::ecs
{
    class SystemManager
    {
    public:
        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            const char* typeName = typeid(T).name();

            assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once");

            auto system = std::make_shared<T>();
            mSystems.insert({typeName, system});
            return system;
        }

        template<typename T>
        void SetSignature(Signature signature)
        {
            const char* typeName = typeid(T).name();

            assert(mSystems.find(typeName) != mSystems.end() && "System used before registering it");

            mSignatures.insert({typeName, signature});
        }

        void EntityDestroyed(Entity entity)
        {
            for(const auto& pair : mSystems)
            {
                const auto& system = pair.second;

                system->mEntities.erase(entity);
            }
        }

        void EntitySignatureChanged(Entity entity, Signature entitySignature)
        {
            for(const auto& pair : mSystems)
            {
                const auto& type = pair.first;
                const auto& system = pair.second;
                const auto& systemSignature = mSignatures[type];

                if((entitySignature & systemSignature) == systemSignature)
                {
                    system->mEntities.insert(entity);
                }
                else
                {
                    system->mEntities.erase(entity);
                }
            }
        }

    private:
        std::unordered_map<const char*, Signature> mSignatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
    };
}

#endif