#include "UninitializedRepoException.h"

namespace MaikoDev {
    namespace Arc {
        namespace Exceptions {
            std::unique_ptr<std::string> UninitializedRepoException::_message = std::make_unique<std::string>("fatal: not a arc repository (or any of the parent directories!): .arc");
            const char* UninitializedRepoException::what() const throw() { return _message->c_str(); };

            UninitializedRepoException::UninitializedRepoException() : ArcRuntimeException() {}
        }
    }
}