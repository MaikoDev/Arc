#include "NonValidCommandException.h"

namespace MaikoDev {
    namespace Arc {
        namespace Exceptions {
            NonValidCommandException::NonValidCommandException(std::unique_ptr<std::string> msg) : ArcRuntimeException(std::move(msg)) {}

            const char* NonValidCommandException::what() const throw() {
                return _exMessage->c_str();
            }
        }
    }
}