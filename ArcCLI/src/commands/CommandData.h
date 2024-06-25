#pragma once

#include <memory>
#include <queue>
#include <commands/CommandType.h>

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            struct CommandData {
                CommandType Type;
                std::queue<std::unique_ptr<std::string>> Arguments;
            };
        }
    }
}