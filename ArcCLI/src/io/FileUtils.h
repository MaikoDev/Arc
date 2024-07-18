#pragma once

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace MaikoDev {
    namespace Arc {
        namespace IO {
            inline const std::string const ConvertToPath(const std::string& directoryPath, const char search, const char replace, size_t reserveLength = 0) {
                const char* path = directoryPath.c_str();
                reserveLength = (reserveLength == 0) ? directoryPath.length() : reserveLength;

                std::string converted;
                converted.reserve(reserveLength);

                for (auto& character : directoryPath) {
                    char selected = (character == search) ? replace : character;

                    converted.push_back(selected);
                }

                return converted;
            }

            inline const std::string const ConvertToUnixPath(const std::string directoryPath) { return ConvertToPath(directoryPath, '\\', '/'); }
            inline const std::string const ConvertToUnixPath(const fs::path directoryPath) { return ConvertToUnixPath(directoryPath.string()); }

            inline const std::string const ConvertToWinPath(const std::string directoryPath) { return ConvertToPath(directoryPath, '/', '\\', directoryPath.length() + directoryPath.length() / 4); }
            inline const std::string const ConvertToWinPath(const fs::path directoryPath) { return ConvertToWinPath(directoryPath.string()); }
        }
    }
}