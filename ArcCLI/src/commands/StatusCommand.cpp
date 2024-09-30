#include "commands/StatusCommand.h"

#include <iostream>

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            StatusCommand::StatusCommand(const fs::path& projectPath) : _projectPath(projectPath) {}

            void StatusCommand::run() {
                std::cout << _projectPath << std::endl;


            }
        }
    }
}