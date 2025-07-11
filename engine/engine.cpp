#include <mnemos.hpp>

#include <core/logging/log.hpp>
#include <core/timer/timer.hpp>

constexpr auto fixedUpdateRate = 60.0f;

namespace mnm
{
    /* MAIN ENGINE LOOP */
    void Run(const std::unique_ptr<MnemosApplication>& app) noexcept
    {
        // TODO - Initialize engine
        app->OnInit();

        u64 accumulator = 0;

        while(true)
        {
            // TODO - Poll input events

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
            timer::CountFrame();
        }

        // TODO - Shutdown engine
        app->OnShutdown();
    }
}
