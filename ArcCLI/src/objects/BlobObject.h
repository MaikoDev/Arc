#pragma once

#include <filesystem>

#include "objects/TrackedObject.h"
#include "objects/TrackedType.h"

#include "io/StagedFile.h"

namespace fs = std::filesystem;

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            class BlobObject : public TrackedObject {
            public:
                BlobObject(const IO::StagedFile& stagedFile);
                BlobObject(const fs::path& blobPath);
                virtual void deserialize(const char* data) override;

                bool hasDiff();
                //FileDiff getDiff(const BlobObject& blob);

            protected:
                virtual const std::string const& getChecksum() override;
                virtual const std::string const& getContent() override;
                virtual const TrackedType& const getType() override { return _trackedType; }
                virtual const std::string& const getTypeStr() override { return Objects::TrackedTypeStr[_trackedType]; }
            private:

                std::unique_ptr<std::string> unzipData();
                std::unique_ptr<std::string> getBlobChecksum();
            private:
                const TrackedType _trackedType = TrackedType::Blob;

                fs::path _path;
                uint64_t _contentSize = 0;

                std::unique_ptr<std::string> _blobData;
                std::unique_ptr<std::string> _checksum;
            };
        }
    }
}