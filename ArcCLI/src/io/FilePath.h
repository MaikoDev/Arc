#pragma once

#include <memory>
#include <filesystem>

namespace FS = std::filesystem;

namespace MaikoDev {
    namespace Arc {
        namespace IO {
            class FilePath {
            public:
                FilePath();
                FilePath(const char* basePath);
                FilePath(const FS::path& basePath);

                static const FilePath& getWorkingDir();

                const std::unique_ptr<FilePath> getRelative(const char* relativePath) const;
                const std::unique_ptr<FilePath> getParent() const;
                const FS::path getAbsolute() const;

                const bool isBasePath() const;
            private:
                //const static FS::path& _workDir;
                static const FilePath _workDir;

                const char* _basePath;
                const char* _relativePath;
                const char* _absolutePath;
            };
        }
    }
}