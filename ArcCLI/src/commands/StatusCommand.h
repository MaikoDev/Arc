#pragma once

#include <commands/ICommand.h>
#include <filesystem>

namespace fs = std::filesystem;

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            class StatusCommand : public ICommand {
            public:
                StatusCommand(const fs::path& projectPath);

                virtual void run() override;
            private:
                const fs::path& _projectPath;
            };
        }
    }
}