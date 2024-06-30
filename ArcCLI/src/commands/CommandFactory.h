#pragma once

#include <memory>
#include <filesystem>

#include <commands/CommandData.h>
#include <commands/ICommand.h>

#include <exceptions/NonValidCommandException.h>

namespace fs = std::filesystem;

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            class CommandFactory {
            public:
                CommandFactory(const fs::path& workDir);

                std::shared_ptr<ICommand> getCommand(std::unique_ptr<CommandData> data);
                const fs::path& getArcPath() const&;
            private:
                const fs::path& _workDir;
                fs::path _arcPath;
            };

            extern inline const std::unique_ptr<CommandData> const extractCommand(int argc, char** args) throw(Exceptions::NonValidCommandException);
        }
    }
}