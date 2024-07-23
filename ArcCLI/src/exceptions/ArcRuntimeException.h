#pragma once

#include <string>
#include <memory>
#include <exception>

namespace MaikoDev {
    namespace Arc {
        namespace Exceptions {
            class ArcRuntimeException : public std::exception {
            public:
                ArcRuntimeException(const char* msg) : _exMessage(std::make_unique<std::string>(msg)) {}
                ArcRuntimeException(std::unique_ptr<std::string> msg) : _exMessage(std::move(msg)) {}
                virtual const char* what() const throw() = 0;
            protected:
                ArcRuntimeException() {}
            protected:
                std::unique_ptr<std::string> _exMessage;
            };
        }
    }
}