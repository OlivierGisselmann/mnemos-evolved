#ifndef TIMER_HPP
#define TIMER_HPP

#include <types.hpp>

#include <chrono>

namespace mnm::timer
{
    void UpdateTimer();

    [[nodiscard]] const u64 GetDeltaTime();
    [[nodiscard]] const u64 GetTotalTime();
}

#endif
