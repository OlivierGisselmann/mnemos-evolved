#include <mnemos.hpp>

#include <core/logging/log.hpp>
#include <core/timer/timer.hpp>
#include <platform/window/window.hpp>

#include <glad/glad.h>

constexpr auto FIXED_UPDATE_RATE = 60.0f;

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

            glClearColor(0.9f, 0.3f, 0.4f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // TODO - Update engine state
            timer::UpdateTimer();
            app->OnUpdate();

            // Fixed timestep update
            accumulator += timer::GetDeltaTime();
            while(accumulator > 1.0f / (FIXED_UPDATE_RATE / 1e9))
            {
                app->OnFixedUpdate();
                accumulator -= 1.0f / (FIXED_UPDATE_RATE / 1e9);
            }
            
            
            // TODO - Render frame
            window.SwapBuffers();
            input::UpdateInputState();
        }

        // Engine shutdown
        app->OnShutdown();

        window.Shutdown();
    }
}
