#include "ArcCLI.h"

#include <iostream>

#include <commands/InitCommand.h>
#include <exceptions/UninitializedRepoException.h>

namespace MaikoDev {
    namespace Arc {
        ArcCLI::ArcCLI(const fs::path& workingDirectory, int argc, char** args) : _workDir(workingDirectory), _commandFactory(_workDir), _arcDir(_commandFactory.getArcPath()) {
            /* Load arc directory */
            bool canLoad = fs::exists(_arcDir);
            if (canLoad) {
                
            }

            std::unique_ptr<Commands::CommandData> commandData = Commands::extractCommand(argc, args);

            if (!canLoad && !(commandData->Type == Commands::CommandType::Help || commandData->Type == Commands::CommandType::Init))
                throw Exceptions::UninitializedRepoException();

            std::shared_ptr<Commands::ICommand> command = _commandFactory.getCommand(std::move(commandData));
        }
    }
}