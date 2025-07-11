#include <core/timer/timer.hpp>

namespace mnm::timer
{
    static auto old = std::chrono::steady_clock::now();
    static auto frameCount = 0;
    static auto fixedUpdateCount = 0;

    // Get delta time in nanoseconds (using integer to avoid floating point inaccuracies)
    u64 GetDeltaTime()
    {
        const auto now = std::chrono::steady_clock::now();

        const auto delta = std::chrono::duration(now - old).count();

        old = now;

        return delta;
    }

    // Get total time in nanoseconds (using integer to avoid floating point inaccuracies)
    u64 GetTotalTime()
    {
        static const auto start = std::chrono::steady_clock::now();

        const auto now = std::chrono::steady_clock::now();

        return std::chrono::duration(now - old).count();
    }

    void CountFrame()
    {
        ++frameCount;
    }

    u64 GetFrameCount()
    {
        return frameCount;
    }

    void CountFixedUpdate()
    {
        ++fixedUpdateCount;
    }

    u64 GetFixedUpdateCount()
    {
        return fixedUpdateCount;
    }
}
