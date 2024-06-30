#include "UninitializedRepoException.h"

namespace MaikoDev {
    namespace Arc {
        namespace Exceptions {
            const char* UninitializedRepoException::_message = "fatal: not a arc repository (or any of the parent directories!): .arc";
            const char* UninitializedRepoException::what() const { return _message; };
        }
    }
}