#pragma once

#include "ArcRuntimeException.h"

namespace MaikoDev {
    namespace Arc {
        namespace Exceptions {
            class UninitializedRepoException : public ArcRuntimeException {
            public:
                UninitializedRepoException();
                const char* what() const throw() override;
            private:
                /*static const char* _message;*/
                static std::unique_ptr<std::string> _message;
            };
        }
    }
}