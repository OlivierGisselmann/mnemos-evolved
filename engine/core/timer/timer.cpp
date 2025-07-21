#include <core/timer/timer.hpp>

namespace mnm::timer
{
    static auto old = std::chrono::steady_clock::now();
    static auto frameCount = 0;
    static auto fixedUpdateCount = 0;

    static u64 totalTime = 0, deltaTime = 0;

    void UpdateTimer()
    {
        static const auto start = std::chrono::steady_clock::now();

        const auto now = std::chrono::steady_clock::now();
        deltaTime = std::chrono::duration(now - old).count();
        totalTime = std::chrono::duration(now - start).count();

        old = now;
    }

    // Get delta time in nanoseconds (using integer to avoid floating point inaccuracies)
    [[nodiscard]] const u64 GetDeltaTime()
    {
        return deltaTime;
    }

    // Get total time in nanoseconds (using integer to avoid floating point inaccuracies)
    [[nodiscard]] const u64 GetTotalTime()
    {
        return totalTime;
    }
}
