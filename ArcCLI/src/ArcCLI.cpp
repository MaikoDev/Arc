#include "ArcCLI.h"

#include <iostream>

#include <commands/InitCommand.h>
#include <exceptions/UninitializedRepoException.h>

namespace MaikoDev {
    namespace Arc {
        ArcCLI::ArcCLI(const fs::path& startDirectory, int argc, char** args) : _startPath(startDirectory) {
            /* Load arc directory */
            fs::path searchPath = _startPath;
            fs::path root = _startPath.root_name();
            fs::path arcPath;
            bool canLoad = false;

            /* Search down to the root to see if any parent directory
             * contains Arc directory.   
             */
            while (searchPath != root) {
                int delimiterIndex = getPathDelimiterIndex(searchPath);
                arcPath = searchPath;

                arcPath.concat("\\.arc");
                if (fs::exists(arcPath)) {
                    canLoad = true;
                    break;
                }

                if (delimiterIndex == -1) break;

                searchPath = searchPath.string().substr(0, delimiterIndex);
            }

            /* Validation */
            if (canLoad) {
                _arcPath = arcPath;
            }
            else {
                _arcPath = _startPath;
                _arcPath.concat("\\.arc");
            }

            _commandFactory = std::make_unique<Commands::CommandFactory>(_startPath, _arcPath);

            std::unique_ptr<Commands::CommandData> commandData = Commands::extractCommand(argc, args);

            if (!canLoad && !(commandData->Type == Commands::CommandType::Help || commandData->Type == Commands::CommandType::Init))
                throw Exceptions::UninitializedRepoException();

            std::shared_ptr<Commands::ICommand> command = _commandFactory->getCommand(std::move(commandData));

            command->run();
        }

        int ArcCLI::getPathDelimiterIndex(const fs::path& currentPath) {
            auto currentPathStr = currentPath.string();
            for (int i = currentPathStr.size() - 1; i >= 0; i--) {
                if (currentPathStr[i] == '\\') return i;
            }

            return -1;
        }
    }
}