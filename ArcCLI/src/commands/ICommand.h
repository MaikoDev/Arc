#pragma once

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            class ICommand {
            public:
                virtual void run() = 0;
            };
        }
    }
}