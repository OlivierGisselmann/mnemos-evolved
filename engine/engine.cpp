#include <mnemos.hpp>

#include <core/logging/log.hpp>
#include <core/timer/timer.hpp>
#include <ecs/core/coordinator.hpp>
#include <ecs/components/renderable.hpp>
#include <ecs/components/transform.hpp>
#include <ecs/systems/render_system.hpp>
#include <platform/window/window.hpp>
#include <renderer/renderer_factory.hpp>

#include <cstdlib>

constexpr auto FIXED_UPDATE_RATE = 60.0f;

unsigned bounded_rand(unsigned range)
{
    for (unsigned x, r;;)
        if (x = rand(), r = x % range, x - r <= -range)
            return r;
}

mnm::ecs::Coordinator gCoordinator;

namespace mnm
{
    // TODO: Refactor this
    static bool sUserSideStop = false;

    /* MAIN ENGINE LOOP */
    void Run(const std::unique_ptr<MnemosApplication>& app) noexcept
    {
        // Subsystems initialization
        window::MWindow window;
        window.Initialize({1280, 720}, "Mnemos Evolved");

        auto renderer = renderer::CreateRenderer(renderer::RendererBackend::OpenGL);
        renderer->Initialize();

        // ECS initialization
        gCoordinator.Init();
        gCoordinator.RegisterComponent<ecs::Renderable>();
        gCoordinator.RegisterComponent<ecs::Transform>();

        auto renderSystem = gCoordinator.RegisterSystem<ecs::RenderSystem>();
        {
            ecs::Signature signature;
            signature.set(gCoordinator.GetComponentType<ecs::Renderable>());
            signature.set(gCoordinator.GetComponentType<ecs::Transform>());
            gCoordinator.SetSystemSignature<ecs::RenderSystem>(signature);
        }

        // Entity initialization
        std::vector<ecs::Entity> entities(100);

        for(auto& entity : entities)
        {
            entity = gCoordinator.CreateEntity();

            gCoordinator.AddComponent(entity, ecs::Transform
            {
                .position = {bounded_rand(10), bounded_rand(10), bounded_rand(20)},
                .rotation = {bounded_rand(180), bounded_rand(180),bounded_rand(180)},
                .scale = {bounded_rand(10)}
            });
            gCoordinator.AddComponent(entity, ecs::Renderable{"../../resources/models/bunny.obj"});
        }

        renderSystem->Init();

        app->OnInit();

        u64 accumulator = 0;
        while(!window.CloseRequested() && !sUserSideStop)
        {
            window.PollEvents();

            timer::UpdateTimer();
            app->OnUpdate((float)(timer::GetDeltaTime() / 1e9));

            for(auto& entity : entities)
            {
                gCoordinator.GetComponent<ecs::Transform>(entity).rotation.x += bounded_rand(3);
                gCoordinator.GetComponent<ecs::Transform>(entity).rotation.y += bounded_rand(3);
                gCoordinator.GetComponent<ecs::Transform>(entity).rotation.z += bounded_rand(3);
            }

            // Fixed timestep update
            accumulator += timer::GetDeltaTime();
            while(accumulator > 1.0 / (FIXED_UPDATE_RATE / 1e9))
            {
                app->OnFixedUpdate();
                accumulator -= 1.0 / (FIXED_UPDATE_RATE / 1e9);
            }     
            
            // Render frame
            renderer->BeginFrame(window.GetSize());
            renderer->DrawFrame(timer::GetDeltaTime() / 1e9);
            renderer->EndFrame();

            renderSystem->Update(timer::GetDeltaTime() / 1e9);

            window.SwapWindowBuffers();
            input::UpdateInputState();
        }

        // Engine shutdown
        app->OnShutdown();

        window.Shutdown();
    }

    // Temporary user-side main loop break
    void Stop() noexcept
    {
        sUserSideStop = true;
    }
}
