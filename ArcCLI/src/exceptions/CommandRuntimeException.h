#pragma once

#include "ArcRuntimeException.h"

#define throwArcCommandException(buffer, format, ...) \
std::snprintf(buffer, sizeof(buffer), \
    format, \
    (objPathEmpty) ? "empty" : "existing" \
);\
\
throw Exceptions::CommandRuntimeException(buffer);\

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