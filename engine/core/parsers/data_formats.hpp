#ifndef DATA_FORMATS_HPP
#define DATA_FORMATS_HPP

#include <types.hpp>

#include <vector>

namespace mnm::parser
{
    struct ImageData {
        int width = 0;
        int height = 0;
        int channels = 0;
        std::vector<u8> pixels;

        bool IsValid() const { return !pixels.empty(); }
    };
}

#endif