#include <mnemos.hpp>

#include <core/logging/log.hpp>
#include <core/timer/timer.hpp>
#include <ecs/core/coordinator.hpp>
#include <ecs/components/renderable.hpp>
#include <ecs/components/transform.hpp>
#include <ecs/systems/render_system.hpp>
#include <platform/window/window.hpp>
#include <renderer/renderer_factory.hpp>

constexpr auto FIXED_UPDATE_RATE = 60.0f;

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
        renderSystem->Init();

        ecs::Entity model1 = gCoordinator.CreateEntity();
        gCoordinator.AddComponent(model1, ecs::Renderable{});
        gCoordinator.AddComponent(model1, ecs::Transform{});

        gCoordinator.GetComponent<ecs::Transform>(model1).position = {2.f, -0.5f, 0.f};
        gCoordinator.GetComponent<ecs::Transform>(model1).scale = {0.5f};

        ecs::Entity model2 = gCoordinator.CreateEntity();
        gCoordinator.AddComponent(model2, ecs::Renderable{});
        gCoordinator.AddComponent(model2, ecs::Transform{});

        gCoordinator.GetComponent<ecs::Transform>(model2).position = {-2.f, -0.5f, 0.f};
        gCoordinator.GetComponent<ecs::Transform>(model2).scale = {0.5f};

        app->OnInit();

        u64 accumulator = 0;
        while(!window.CloseRequested() && !sUserSideStop)
        {
            window.PollEvents();

            // TODO - Update engine state
            timer::UpdateTimer();
            app->OnUpdate((float)(timer::GetDeltaTime() / 1e9));

            gCoordinator.GetComponent<ecs::Transform>(model1).rotation.x += (timer::GetDeltaTime() / 1e7);
            gCoordinator.GetComponent<ecs::Transform>(model2).rotation.y += (timer::GetDeltaTime() / 1e7);

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
