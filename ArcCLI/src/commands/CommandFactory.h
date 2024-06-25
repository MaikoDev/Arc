#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>

#include <commands/CommandData.h>
#include <commands/ICommand.h>

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            class CommandFactory {
            public:
                std::shared_ptr<ICommand> getCommand(std::unique_ptr<CommandData> data);
            };

            extern inline const std::unique_ptr<CommandData> const extractCommand(int argc, char** args);
        }
    }
}