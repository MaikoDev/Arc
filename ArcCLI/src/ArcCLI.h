#pragma once

#include <filesystem>
#include <exception>

#include <commands/CommandFactory.h>

namespace fs = std::filesystem;

namespace MaikoDev {
    namespace Arc {
        class ArcCLI {
        public:
            ArcCLI(const fs::path& startDirectory, int argc, char** args) throw(std::exception);       
        private:
            int getPathDelimiterIndex(const fs::path& currentPath);
        private:
            const fs::path& _startPath;
            fs::path _arcPath;
            fs::directory_entry _workingDir;
            std::unique_ptr<Commands::CommandFactory> _commandFactory = nullptr;
        };
    }
}