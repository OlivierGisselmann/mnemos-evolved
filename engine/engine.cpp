#include <mnemos.hpp>
#include <debug.hpp>

#include <core/logging/log.hpp>

namespace mnm
{
    /* MAIN ENGINE LOOP */
    void Run(const std::unique_ptr<MnemosApplication>& app) noexcept
    {
        app->OnInit();

        app->OnUpdate();

        app->OnFixedUpdate();

        app->OnShutdown();
    }
}

namespace mnm::debug
{
    void Log(const char* message) noexcept
    {
        log::Log(log::Level::DEBUG, log::Channel::APPLICATION, message);
    }
}
