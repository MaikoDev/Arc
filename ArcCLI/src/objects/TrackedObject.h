#pragma once

#include <sstream>

#include "openssl/sha.h"

#include "io/ISerializable.h"
#include "objects/TrackedType.h"

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

                std::unique_ptr<std::string> checksumCalculate(const std::string& input);
            private:
                unsigned char _checksumHash[SHA256_DIGEST_LENGTH];
                std::stringstream _stringBuilder;
            };
        }
    }
}