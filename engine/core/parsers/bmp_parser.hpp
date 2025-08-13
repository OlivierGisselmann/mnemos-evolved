#ifndef BMP_PARSER_HPP
#define BMP_PARSER_HPP

#include <core/parsers/data_formats.hpp>
#include <core/logging/log.hpp>

#include <fstream>
#include <string>

namespace mnm::parser
{
    #pragma pack(push, 1) // Ensure no padding in structs
    struct BMPFileHeader
    {
        u16 fileType{0x4D42}; // "BM"
        u32 fileSize{0};
        u16 reserved1{0};
        u16 reserved2{0};
        u32 dataOffset{0};
    };

    struct BMPInfoHeader
    {
        u32 size{0};
        i32 width{0};
        i32 height{0};
        u16 planes{1};
        u16 bitCount{0};
        u32 compression{0};
        u32 imageSize{0};
        i32 xPixelsPerMeter{0};
        i32 yPixelsPerMeter{0};
        u32 colorsUsed{0};
        u32 colorsImportant{0};
    };
    #pragma pack(pop)

    inline ImageData ReadBMP(const std::string& path) noexcept
    {
        ImageData image;

        // Open file
        std::ifstream file;
        file.open(path, std::ios::in | std::ios::binary);

        if(!file.is_open())
        {
            log::Log(log::Level::ERR, log::Channel::FILESYSTEM, std::format("Failed to open file: {}", path));
            file.close();
            return {};
        }

        // Default value headers
        BMPFileHeader fileHeader;
        BMPInfoHeader infoHeader;

        // Read file's header to get informations
        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
        file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

        if(fileHeader.fileType != 0x4D42)
        {
            log::Log(log::Level::ERR, log::Channel::FILESYSTEM, std::format("Unsupported format: {}", path));
            file.close();
            return {};
        }

        if(infoHeader.bitCount != 24 && infoHeader.bitCount != 32)
        {
            log::Log(log::Level::ERR, log::Channel::FILESYSTEM, std::format("Only 24-bit and 32-bit BMP are supported: {}", path));
            file.close();
            return {};
        }

        // Get image dimensions
        image.width = infoHeader.width;
        image.height = infoHeader.height;
        bool flipVertically = (infoHeader.height > 0);

        // Get pixel format and row padding
        sizet bytesPerPixel = infoHeader.bitCount / 8;
        sizet rowPadded = (image.width * bytesPerPixel + 3) & (~3); // Padded to multiple of 4

        // Make room for all pixels
        std::vector<u8> rowData(rowPadded);
        image.pixels.resize(image.width * image.height * bytesPerPixel);

        // Go to pixel data
        file.seekg(fileHeader.dataOffset, std::ios::beg);

        for(int y = 0; y < image.height; ++y)
        {
            file.read(reinterpret_cast<char*>(rowData.data()), rowPadded);

            u8* dest;
            if(flipVertically)
                dest = image.pixels.data() + (image.height - 1 - y) * image.width * bytesPerPixel;
            else
                dest = image.pixels.data() + y * image.width * bytesPerPixel;

            for(int x = 0; x < image.width; ++x)
            {
                dest[x * bytesPerPixel + 0] = rowData[x * bytesPerPixel + 2]; // R
                dest[x * bytesPerPixel + 1] = rowData[x * bytesPerPixel + 1]; // G
                dest[x * bytesPerPixel + 2] = rowData[x * bytesPerPixel + 0]; // B

                if(bytesPerPixel == 4)
                    dest[x * bytesPerPixel + 3] = rowData[x * bytesPerPixel + 3]; // A
            }
        }

        file.close();

        return image;
    }
}

#endif