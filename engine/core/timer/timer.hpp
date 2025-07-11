#ifndef TIMER_HPP
#define TIMER_HPP

#include <platform/types.hpp>

#include <chrono>

namespace mnm::timer
{
    u64 GetDeltaTime();
    u64 GetTotalTime();

    u64 GetFrameCount();
    void CountFrame();

    u64 GetFixedUpdateCount();
    void CountFixedUpdate();
}

#endif
