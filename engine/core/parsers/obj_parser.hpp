#ifndef OBJ_PARSER_HPP
#define OBJ_PARSER_HPP

#include <core/logging/log.hpp>
#include <core/parsers/data_formats.hpp>
#include <renderer/structs/vertex.hpp>

#include <algorithm>
#include <fstream>
#include <unordered_map>

namespace mnm::parser
{
    struct VertexHash {
        sizet operator()(const renderer::Vertex& v) const {
            auto h1 = std::hash<float>()(v.position.x) ^ (std::hash<float>()(v.position.y) << 1);
            auto h2 = std::hash<float>()(v.position.z) ^ (std::hash<float>()(v.texCoords.x) << 1);
            auto h3 = std::hash<float>()(v.texCoords.y) ^ (std::hash<float>()(v.normal.x) << 1);
            auto h4 = std::hash<float>()(v.normal.y) ^ (std::hash<float>()(v.normal.z) << 1);
            return h1 ^ h2 ^ h3 ^ h4;
        }
    };

    inline MeshData* ReadOBJ(const std::string& path)
    {
        static std::unordered_map<std::string, MeshData> cache;

        // Return cached data if exists
        if(cache.find(path) != cache.end())
            return &cache[path];

        // Open file
        std::ifstream file(path);
        if(!file)
        {
            log::Log(log::Level::ERR, log::Channel::FILESYSTEM, std::format("Could not open file: {}", path));
            return nullptr;
        }

        MeshData mesh;

        std::vector<math::Vec3f> positions;
        std::vector<math::Vec3f> normal;
        std::vector<math::Vec2f> texCoords;

        std::unordered_map<renderer::Vertex, u32, VertexHash> vertexToIndex;

        // Read file line by line
        std::string line;
        while(std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if(prefix == "v") // Position
            {
                math::Vec3f pos;
                iss >> pos.x >> pos.y >> pos.z;
                positions.push_back(pos);
            }
            else if(prefix == "vn") // Normal
            {
                math::Vec3f nrm;
                iss >> nrm.x >> nrm.y >> nrm.z;
                normal.push_back(nrm);
            }
            else if(prefix == "vt") // Texture Coordinates
            {
                math::Vec2f uv;
                iss >> uv.x >> uv.y;
                texCoords.push_back(uv);
            }
            else if(prefix == "f") // Indices
            {
                std::string vertexStr;
                for(int i = 0; i < 3; ++i)
                {
                    iss >> vertexStr;
                    std::replace(vertexStr.begin(), vertexStr.end(), '/', ' ');
                    std::istringstream viss(vertexStr);

                    int pi = 0, ti = 0, ni = 0;
                    viss >> pi >> ti >> ni;

                    renderer::Vertex vertex{};
                    vertex.position = positions[pi - 1];
                    vertex.normal = (ni > 0) ? normal[ni - 1] : math::Vec3f(0.f);
                    vertex.texCoords = (ti > 0) ? texCoords[ti - 1] : math::Vec2f(0.f);

                    // Reuse vertex if already in cache
                    if(vertexToIndex.count(vertex) == 0)
                    {
                        u32 index = static_cast<u32>(mesh.vertices.size());
                        mesh.vertices.push_back(vertex);
                        vertexToIndex[vertex] = index;
                    }

                    mesh.indices.push_back(vertexToIndex[vertex]);
                }
            }
        }

        // Add Mesh Data to cache
        cache.insert({path, mesh});

        log::Log(log::Level::DEBUG, log::Channel::FILESYSTEM, std::format("{} loaded!", path));

        return &cache[path];
    }
}

#endif