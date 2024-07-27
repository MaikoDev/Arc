#pragma once

#include <vector>
#include <memory>
#include <filesystem>

#include <objects/TrackedObject.h>
#include <objects/BlobObject.h>

namespace fs = std::filesystem;

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            class TreeObject : public TrackedObject {
            public:
                TreeObject(const fs::path root);
                virtual void deserialize(const char* data) override;
            protected:
                virtual const std::string const& getChecksum() override { return *_checksum; }
                virtual const std::string const& getContent() override { return *_contentStructure; }
                virtual const TrackedType& const getType() override { return _trackedType; }
                virtual const std::string& const getTypeStr() override { return Objects::TrackedTypeStr[_trackedType]; }
            private:
                const std::unique_ptr<TreeObject> const _createBranch(const fs::path parentPath);
                const std::unique_ptr<BlobObject> const _createBlob(const fs::path path);
            private:
                const fs::path _rootPath;
                const TrackedType _trackedType = TrackedType::Tree;

                std::vector<std::shared_ptr<TreeObject>> _subDirectories;
                std::vector<std::shared_ptr<BlobObject>> _fileBlobs;

                std::unique_ptr<std::string> _contentStructure;
                std::unique_ptr<std::string> _checksum;
            };
        }
    }
}