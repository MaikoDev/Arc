#pragma once

#include "ArcRuntimeException.h"

namespace MaikoDev {
    namespace Arc {
        namespace Exceptions {
            class CommandRuntimeException : public ArcRuntimeException {
            public:
                CommandRuntimeException(const char* msg);
                CommandRuntimeException(std::unique_ptr<std::string> msg);
                virtual const char* what() const throw() override;
            };
        }
    }
}