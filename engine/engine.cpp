#include <mnemos.hpp>

#include <core/logging/log.hpp>
#include <core/timer/timer.hpp>
#include <ecs/core/coordinator.hpp>
#include <ecs/systems/camera_system.hpp>
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

        auto shader = std::make_shared<renderer::opengl::Shader>("../../resources/shaders/test.vert", "../../resources/shaders/test.frag");

        // ECS initialization
        gCoordinator.Init();
        gCoordinator.RegisterComponent<ecs::Camera>();
        gCoordinator.RegisterComponent<ecs::Renderable>();
        gCoordinator.RegisterComponent<ecs::Transform>();

        auto renderSystem = gCoordinator.RegisterSystem<ecs::RenderSystem>();
        {
            ecs::Signature signature;
            signature.set(gCoordinator.GetComponentType<ecs::Renderable>());
            signature.set(gCoordinator.GetComponentType<ecs::Transform>());
            gCoordinator.SetSystemSignature<ecs::RenderSystem>(signature);
        }

        auto cameraSystem = gCoordinator.RegisterSystem<ecs::CameraSystem>();
        {
            ecs::Signature signature;
            signature.set(gCoordinator.GetComponentType<ecs::Camera>());
            gCoordinator.SetSystemSignature<ecs::CameraSystem>(signature);
        }

        // Entity initialization
        std::vector<ecs::Entity> entities(100);

        for(auto& entity : entities)
        {
            entity = gCoordinator.CreateEntity();

            gCoordinator.AddComponent(entity, ecs::Transform
            {
                .position = {(float)(std::rand() % 10)},
                .rotation = {(float)(std::rand() % 180)},
                .scale = {(float)(std::rand() % 10)}
            });
            gCoordinator.AddComponent(entity, ecs::Renderable{"../../resources/models/bunny.obj"});
        }

        // Camera setup
        auto camera = gCoordinator.CreateEntity();
        gCoordinator.AddComponent(camera, ecs::Camera{});

        renderSystem->Init(shader);
        cameraSystem->Init(shader);

        app->OnInit();

        /* MAIN LOOP */
        u64 accumulator = 0;
        while(!window.CloseRequested() && !sUserSideStop)
        {
            window.PollEvents();

            timer::UpdateTimer();
            auto deltaTimeInSeconds = timer::GetDeltaTime() / 1e9;
            app->OnUpdate((float)(deltaTimeInSeconds));

            for(auto& entity : entities)
            {
                gCoordinator.GetComponent<ecs::Transform>(entity).rotation.x += (float)(std::rand() % 3);
                gCoordinator.GetComponent<ecs::Transform>(entity).rotation.y += (float)(std::rand() % 3);
                gCoordinator.GetComponent<ecs::Transform>(entity).rotation.z += (float)(std::rand() % 3);
            }

            /* FIXED TIMESTEP UPDATE */
            accumulator += timer::GetDeltaTime();
            while(accumulator > 1.0 / (FIXED_UPDATE_RATE / 1e9))
            {
                app->OnFixedUpdate();
                accumulator -= 1.0 / (FIXED_UPDATE_RATE / 1e9);
            }     
            
            // Render frame
            renderer->BeginFrame(window.GetSize());
            renderer->DrawFrame(deltaTimeInSeconds);
            renderer->EndFrame();

            cameraSystem->Update(deltaTimeInSeconds, window.GetSize());
            renderSystem->Update(deltaTimeInSeconds);

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
