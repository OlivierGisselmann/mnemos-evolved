#include <debug.hpp>

#include <core/logging/log.hpp>

namespace mnm::debug
{
    void Log(const char* message) noexcept
    {
        log::Log(log::Level::DEBUG, log::Channel::APPLICATION, message);
    }
}