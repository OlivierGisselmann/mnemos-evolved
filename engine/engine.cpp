#include <mnemos.hpp>

#include <core/logging/log.hpp>
#include <core/timer/timer.hpp>
#include <ecs/core/coordinator.hpp>
#include <ecs/systems/camera_system.hpp>
#include <ecs/systems/light_system.hpp>
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
        gCoordinator.RegisterComponent<ecs::DirectionalLight>();
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

        auto lightSystem = gCoordinator.RegisterSystem<ecs::LightSystem>();
        {
            ecs::Signature signature;
            signature.set(gCoordinator.GetComponentType<ecs::DirectionalLight>());
            gCoordinator.SetSystemSignature<ecs::LightSystem>(signature);
        }

        // Model entity
        auto model = gCoordinator.CreateEntity();
        gCoordinator.AddComponent(model, ecs::Transform
        {
            .position = {0.f, -0.5f, 0.f},
            .rotation = {0.f},
            .scale = {1.f}
        });
        gCoordinator.AddComponent(model, ecs::Renderable{"../../resources/models/bunny.obj"});

        // Camera entity
        auto camera = gCoordinator.CreateEntity();
        gCoordinator.AddComponent(camera, ecs::Camera{});
        gCoordinator.GetComponent<ecs::Camera>(camera).position = {0.f, 0.f, -5.f};

        // Light entity
        auto light = gCoordinator.CreateEntity();
        gCoordinator.AddComponent(light, ecs::DirectionalLight{
            .position = {0.f, 3.f, 0.f},
            .color = {1.f, 0.f, 0.f},
            .intensity = 1.f
        });

        // ECS systems initialization
        renderSystem->Init(shader);
        cameraSystem->Init(shader);
        lightSystem->Init(shader);

        app->OnInit();

        /* MAIN LOOP */
        u64 accumulator = 0;
        while(!window.CloseRequested() && !sUserSideStop)
        {
            window.PollEvents();

            // Update timer and calculate delta time
            timer::UpdateTimer();
            auto deltaTimeInSeconds = timer::GetDeltaTime() / 1e9;
            app->OnUpdate((float)(deltaTimeInSeconds));

            // Rotate model
            gCoordinator.GetComponent<ecs::Transform>(model).rotation += {0.f, deltaTimeInSeconds * 10.0, 0.f};

            /* FIXED TIMESTEP UPDATE */
            accumulator += timer::GetDeltaTime();
            while(accumulator > 1.0 / (FIXED_UPDATE_RATE / 1e9))
            {
                app->OnFixedUpdate();
                accumulator -= 1.0 / (FIXED_UPDATE_RATE / 1e9);
            }

            shader->SetUniform("ambient", math::Vec3f{1.f});
            shader->SetUniform("diffuse", math::Vec3f{1.f});
            shader->SetUniform("specular", math::Vec3f{1.f});
            
            // Render frame
            renderer->BeginFrame(window.GetSize());
            renderer->DrawFrame(deltaTimeInSeconds);
            renderer->EndFrame();

            // Update ECS systems
            cameraSystem->Update(deltaTimeInSeconds, window.GetSize());
            renderSystem->Update(deltaTimeInSeconds);
            lightSystem->Update();

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
