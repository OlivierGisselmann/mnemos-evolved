#include <core/filesystem/filesystem.hpp>

namespace mnm::file
{
    const std::string ReadFile(const std::string& path)
    {
        std::ifstream file(path);

        if(!file)
        {
            std::stringstream ss;
            ss << "Failed to open file: " << path;
            log::Log(log::Level::ERR, log::Channel::GLOBAL, ss.str());
            return "";
        }

        std::stringstream content;
        content << file.rdbuf();
        file.close();

        return content.str();
    }
}
