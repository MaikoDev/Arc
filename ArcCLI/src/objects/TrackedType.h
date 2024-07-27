#pragma once

#include <memory>
#include <string>

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            enum TrackedType {
                Commit,
                Tree,
                Blob
            };

            const std::string const TrackedTypeStr[] = {
                "Commit",
                "Tree",
                "Blob"
            };
        }
    }
}