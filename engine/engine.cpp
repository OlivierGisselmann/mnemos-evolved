#include <mnemos.hpp>

#include <core/logging/log.hpp>
#include <core/timer/timer.hpp>
#include <platform/window/window.hpp>
#include <renderer/renderer_factory.hpp>

constexpr auto FIXED_UPDATE_RATE = 10.0f;

namespace mnm
{
    /* MAIN ENGINE LOOP */
    void Run(const std::unique_ptr<MnemosApplication>& app) noexcept
    {
        // Subsystems initialization
        window::MWindow window;
        window.Initialize(1280, 720, "Mnemos Evolved");
        auto renderer = renderer::RendererFactory::Create(renderer::RendererBackend::OpenGL);

        app->OnInit();

        u64 accumulator = 0;
        while(!window.CloseRequested())
        {
            window.PollEvents();

            // TODO - Update engine state
            timer::UpdateTimer();
            app->OnUpdate();

            // Fixed timestep update
            accumulator += timer::GetDeltaTime();
            while(accumulator > 1.0f / (FIXED_UPDATE_RATE / 1e9))
            {
                app->OnFixedUpdate();
                accumulator -= 1.0f / (FIXED_UPDATE_RATE / 1e9);
                LOG("Fixed Update");
            }     
            
            renderer->BeginFrame();
            renderer->DrawFrame();
            renderer->EndFrame();

            window.SwapBuffers();
            input::UpdateInputState();
        }

        // Engine shutdown
        app->OnShutdown();

        window.Shutdown();
    }
}
