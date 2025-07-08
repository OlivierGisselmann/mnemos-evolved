#include <core/logging/log.hpp>

namespace mnm::log
{
    void Log(const Level level, const Channel channel, const std::string& message)
    {
        std::cout << LevelToString(level) << ChannelToString(channel) << " " << message << '\n';
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
        case INPUT:         return "[INPUT]";
        default:            return "[UNKNOWN]";
        }
    }
}
