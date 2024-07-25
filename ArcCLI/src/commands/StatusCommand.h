#pragma once

#include <commands/ICommand.h>

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            class StatusCommand : public ICommand {
            public:
                virtual void run() override;
            };
        }
    }
}