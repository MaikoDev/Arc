#pragma once

#include <filesystem>
#include "ICommand.h"

namespace fs = std::filesystem;

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            class AddCommand : public ICommand {
            public:
                AddCommand(const fs::path filePath);
                AddCommand(const std::vector<fs::path> filePaths);

                virtual void run() override;
            private:
                std::vector<fs::path> _filePaths;
            };
        }
    }
}