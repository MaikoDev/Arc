#pragma once

#include <filesystem>
#include <exception>

#include <commands/CommandFactory.h>

namespace fs = std::filesystem;

namespace MaikoDev {
    namespace Arc {
        class ArcCLI {
        public:
            ArcCLI(const fs::path& workingDirectory, int argc, char** args) throw(std::exception);

        private:
            void logUnknownCommand(const std::string& commandText);
        private:
            const fs::path& _workDir;
            const fs::path& _arcDir;
            fs::directory_entry _workingDir;
            Commands::CommandFactory _commandFactory;
        };
    }
}