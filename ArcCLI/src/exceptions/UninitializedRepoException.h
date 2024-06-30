#pragma once

#include <exception>

namespace MaikoDev {
    namespace Arc {
        namespace Exceptions {
            class UninitializedRepoException : public std::exception {
            public:
                const char* what() const throw();
            private:
                static const char* _message;
            };
        }
    }
}