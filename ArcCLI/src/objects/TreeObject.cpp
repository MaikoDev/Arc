#include "TreeObject.h"

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            TreeObject::TreeObject(const fs::path path) : _rootPath(path) {
                for (auto const& dir : fs::directory_iterator(_rootPath)) {
                    // Check if the directory is a file or folder
                    if (dir.is_directory()) {
                        auto branch = _createBranch(dir.path());

                        _subDirectories.push_back(std::move(branch));
                    }
                    else {
                        auto blob = _createBlob(dir.path());

                        _fileBlobs.push_back(std::move(blob));
                    }
                }
            }

            void TreeObject::deserialize(const char* data) {

            }

            const std::unique_ptr<TreeObject> const TreeObject::_createBranch(const fs::path path) {
                std::unique_ptr<TreeObject> branch = std::make_unique<TreeObject>(path);
                return branch;
            }

            const std::unique_ptr<BlobObject> const TreeObject::_createBlob(const fs::path path) {
                std::unique_ptr<BlobObject> branch = std::make_unique<BlobObject>(path);
                return branch;
            }
        }
    }
}