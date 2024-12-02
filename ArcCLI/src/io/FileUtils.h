#pragma once

#include <string>
#include <fstream>
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

            inline std::unique_ptr<std::string> readFile(const fs::path& path, const size_t fileSize = 0) {
                std::unique_ptr<std::string> fileData = std::make_unique<std::string>();
                if (fileSize != 0) fileData->reserve(fileSize);

                std::ifstream file(path);
                std::string fileLine;

                while (std::getline(file, fileLine)) {
                    fileData->append(fileLine);
                    fileData->push_back('\n');
                }

                return fileData;
            }

            inline std::streampos GetFileSize(std::ifstream& file) {
                std::streampos size;

                file.seekg(0, std::ios::end);
                size = file.tellg();
                file.seekg(0, std::ios::beg);

                return size;
            }
        }
    }
}