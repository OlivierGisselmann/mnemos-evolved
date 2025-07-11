#ifndef TIMER_HPP
#define TIMER_HPP

#include <platform/types.hpp>

#include <chrono>

namespace mnm::timer
{
    u64 GetDeltaTime();
    u64 GetTotalTime();
    i32 GetFrameCount();
}

#endif
