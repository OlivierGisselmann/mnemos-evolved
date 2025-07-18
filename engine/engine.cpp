#include <mnemos.hpp>

#include <core/logging/log.hpp>
#include <core/timer/timer.hpp>
#include <platform/window/window.hpp>

constexpr auto fixedUpdateRate = 60.0f;

namespace mnm
{
    /* MAIN ENGINE LOOP */
    void Run(const std::unique_ptr<MnemosApplication>& app) noexcept
    {
        // Subsystems initialization
        window::MWindow window;
        window.Initialize(1280, 720, "Mnemos Evolved");

        app->OnInit();

        u64 accumulator = 0;
        while(!window.CloseRequested())
        {
            window.PollEvents();

            // TODO - Update engine state
            app->OnUpdate();

            // Fixed timestep update
            accumulator += timer::GetDeltaTime();
            while(accumulator > 1.0f / (fixedUpdateRate / 1e9))
            {
                app->OnFixedUpdate();
                timer::CountFixedUpdate();
                accumulator -= 1.0f / (fixedUpdateRate / 1e9);
            }
            
            // TODO - Render frame
            window.SwapBuffers();
            timer::CountFrame();
        }

        // Engine shutdown
        app->OnShutdown();

        window.Shutdown();
    }
}
