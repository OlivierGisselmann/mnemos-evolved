#include <core/logging/log.hpp>

namespace mnm::log
{
    void Log(const Level level, const Channel channel, const std::string& message)
    {
        std::cout << GetTime() << LevelToString(level) << ChannelToString(channel) << " " << message << '\n';
    }

    [[nodiscard]] std::string LevelToString(const Level level)
    {
        switch (level)
        {
        case DEBUG:     return "[DEBUG]";
        case INFO:      return "[INFO]";
        case WARN:      return "[WARN]";
        case ERR:       return "[ERR]";
        case FATAL:     return "[FATAL]";
        default:        return "[UNKNOWN]";
        }
    }

    [[nodiscard]] std::string ChannelToString(const Channel channel)
    {
        switch (channel)
        {
        case GLOBAL:        return "[GLOBAL]";
        case APPLICATION:   return "[APPLICATION]";
        case WINDOW:        return "[WINDOW]";
        case RENDERER:      return "[RENDERER]";
        case FILESYSTEM:    return "[FILESYSTEM]";
        case INPUT:         return "[INPUT]";
        default:            return "[UNKNOWN]";
        }
    }

    [[nodiscard]] std::string GetTime()
    {
        const auto time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());

        return std::format("[{:%X}]", time);
    }
}
