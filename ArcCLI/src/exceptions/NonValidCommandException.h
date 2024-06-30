#pragma once

#include <string>
#include <exception>
#include <memory>

namespace MaikoDev {
    namespace Arc {
        namespace Exceptions {
            class NonValidCommandException : public std::exception {
            public:
                NonValidCommandException(std::unique_ptr<std::string> msg) : _message(std::move(msg)) {}

                const char* what() const throw() { return _message->c_str(); }
            private:
                std::unique_ptr<std::string> _message;
            };
        }
    }
}