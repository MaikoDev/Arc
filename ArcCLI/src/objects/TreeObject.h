#pragma once

#include <vector>

#include <objects/TrackedObject.h>
#include <objects/BlobObject.h>

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            class TreeObject : public TrackedObject {
            public:
                virtual void deserialize(const char*) override;

            protected:
                virtual const std::string const& getChecksum() override;
                virtual const std::string const& getContent() override;
                virtual const TrackedType& const getType() override;
                virtual const std::string& const getTypeStr() override;
            private:
                std::vector<std::shared_ptr<TreeObject>> _subDirectories;
                std::vector<std::shared_ptr<BlobObject>> _fileBlobs;
            };
        }
    }
}