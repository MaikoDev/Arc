#pragma once

#include <filesystem>

#include "objects/TrackedObject.h"
#include "objects/TrackedType.h"

namespace fs = std::filesystem;

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            class BlobObject : public TrackedObject {
            public:
                BlobObject(const fs::path path);
                virtual void deserialize(const char* data) override;
            protected:
                virtual const std::string const& getChecksum() override { return *_checksum; }
                virtual const std::string const& getContent() override { return *_blobData; }
                virtual const TrackedType& const getType() override { return _trackedType; }
                virtual const std::string& const getTypeStr() override { return Objects::TrackedTypeStr[_trackedType]; }
            private:
                const fs::path _path;
                const TrackedType _trackedType = TrackedType::Blob;

                std::unique_ptr<std::string> _blobData;
                std::unique_ptr<std::string> _checksum;
            };
        }
    }
}