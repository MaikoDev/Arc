#pragma once

#include "ArcRuntimeException.h"

namespace MaikoDev {
    namespace Arc {
        namespace Exceptions {
            class NonValidCommandException : public ArcRuntimeException {
            public:
                NonValidCommandException(std::unique_ptr<std::string> msg);
                virtual const char* what() const throw() override;
            };
        }
    }
}