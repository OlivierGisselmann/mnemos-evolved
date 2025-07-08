#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>

namespace mnm::log
{
    enum Level
    {
        DEBUG,
        INFO,
        WARN,
        ERR,
        FATAL
    };

    enum Channel
    {
        GLOBAL,
        APPLICATION,
        WINDOW,
        RENDERER,
        INPUT
    };

    void Log(const Level level, const Channel channel, const std::string& message);

    [[nodiscard]] std::string LevelToString(const Level level);
    [[nodiscard]] std::string ChannelToString(const Channel channel);
}

#endif
