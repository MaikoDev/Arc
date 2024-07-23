#include "CommandRuntimeException.h"

namespace MaikoDev {
    namespace Arc {
        namespace Exceptions {
            CommandRuntimeException::CommandRuntimeException(const char* msg) : ArcRuntimeException(msg) {}
            CommandRuntimeException::CommandRuntimeException(std::unique_ptr<std::string> msg) : ArcRuntimeException(std::move(msg)) {}

            const char* CommandRuntimeException::what() const throw() { return _exMessage->c_str(); }
        }
    }
}