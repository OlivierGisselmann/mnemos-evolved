#ifndef LOG_HPP
#define LOG_HPP

#include <chrono>
#include <format>
#include <iostream>
#include <string>
#include <sstream>

#define LOG(message)    Log(mnm::log::Level::DEBUG, mnm::log::Channel::GLOBAL, message)
#define LOG_INFO(message)    Log(mnm::log::Level::INFO, mnm::log::Channel::GLOBAL, message)
#define LOG_WARN(message)    Log(mnm::log::Level::WARNmnm::log::Channel::GLOBAL, message)
#define LOG_ERR(message)    Log(mnm::log::Level::ERR, mnm::log::Channel::GLOBAL, message)
#define LOG_FATAL(message)    Log(mnm::log::Level::FATAL, mnm::log::Channel::GLOBAL, message)

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
        FILESYSTEM,
        INPUT
    };

    void Log(const Level level, const Channel channel, const std::string& message);

    [[nodiscard]] std::string LevelToString(const Level level);
    [[nodiscard]] std::string ChannelToString(const Channel channel);
    [[nodiscard]] std::string GetTime();
}

#endif
