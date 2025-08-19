#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include <ecs/core/entity_manager.hpp>
#include <ecs/core/component_manager.hpp>
#include <ecs/core/system_manager.hpp>

namespace mnm::ecs
{
    class Coordinator
    {
    public:
        void Init()
        {
            mEntityManager = std::make_unique<EntityManager>();
            mComponentManager = std::make_unique<ComponentManager>();
            mSystemManager = std::make_unique<SystemManager>();
        }

        // Entities
        Entity CreateEntity()
        {
            return mEntityManager->CreateEntity();
        }

        void DestroyEntity(Entity entity)
        {
            mEntityManager->DestroyEntity(entity);
            mComponentManager->EntityDestroyed(entity);
            mSystemManager->EntityDestroyed(entity);
        }

        // Components
        template<typename T>
        void RegisterComponent()
        {
            mComponentManager->RegisterComponent<T>();
        }

        template<typename T>
        void AddComponent(Entity entity, T component)
        {
            mComponentManager->AddComponent<T>(entity, component);

            auto signature = mEntityManager->GetSignature(entity);
            signature.set(mComponentManager->GetComponentType<T>(), true);
            mEntityManager->SetSignature(entity, signature);

            mSystemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        T& GetComponent(Entity entity)
        {
            return mComponentManager->GetComponent<T>(entity);
        }

        template<typename T>
        ComponentType GetComponentType()
        {
            return mComponentManager->GetComponentType<T>();
        }

        // Systems
        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            return mSystemManager->RegisterSystem<T>();
        }

        template<typename T>
        void SetSystemSignature(Signature signature)
        {
            mSystemManager->SetSignature<T>(signature);
        }

    private:
        std::unique_ptr<EntityManager> mEntityManager;
        std::unique_ptr<ComponentManager> mComponentManager;
        std::unique_ptr<SystemManager> mSystemManager;
    };
}

#endif