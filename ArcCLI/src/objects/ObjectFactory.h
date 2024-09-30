#pragma once

#include "TreeObject.h"
#include "BlobObject.h"

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            class ObjectFactory {
            public:
                std::shared_ptr<ObjectFactory> getInstance();
                std::unique_ptr<TreeObject> createTree(const fs::path& path);
                std::unique_ptr<BlobObject> createBlob(const fs::path filePath);
            private:
                ObjectFactory() {}
            private:
                static std::shared_ptr<ObjectFactory> _instance;
            };
        }
    }
}