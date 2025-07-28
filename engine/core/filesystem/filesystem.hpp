#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <types.hpp>
#include <core/logging/log.hpp>

#include <fstream>
#include <sstream>

namespace mnm::file
{
    const std::string ReadFile(const std::string& path);
}

#endif
