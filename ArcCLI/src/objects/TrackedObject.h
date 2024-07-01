#pragma once

#include <objects/TrackedType.h>

#include <io/ISerializable.h>

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            class TrackedObject : public IO::ISerializable {
            public:
                virtual const std::string const serialize() override;
            protected:
                virtual const std::string const& getChecksum() = 0;
                virtual const std::string const& getContent() = 0;
                virtual const TrackedType& const getType() = 0;
                virtual const std::string& const getTypeStr() = 0;
            };
        }
    }
}