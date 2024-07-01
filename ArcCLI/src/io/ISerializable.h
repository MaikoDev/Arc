#pragma once

#include <iostream>

namespace MaikoDev {
    namespace Arc {
        namespace IO {
            class ISerializable {
            public:
                virtual const std::string const serialize() = 0;
                virtual void deserialize(const char*) = 0;
            };
        }
    }
}