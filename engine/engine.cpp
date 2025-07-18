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
        window::MWindow window;
        window.Initialize(1280, 720, "Mnemos Evolved");

        // TODO - Initialize engine
        app->OnInit();

        // Loop values initialization
        u64 accumulator = 0;
        bool quit = false;

        while(!quit)
        {
            // TODO - Poll input events
            window.PollEvents();
            quit = window.CloseRequested();

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

            // Temporary loop exit
            if(timer::GetFixedUpdateCount() > 600)
                quit = true;
        }

        // TODO - Shutdown engine
        app->OnShutdown();
    }
}
