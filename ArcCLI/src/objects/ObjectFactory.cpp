#include "ObjectFactory.h"

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            std::shared_ptr<ObjectFactory> ObjectFactory::_instance = nullptr;

            std::shared_ptr<ObjectFactory> ObjectFactory::getInstance() {
                _instance = (_instance) ? _instance : std::shared_ptr<ObjectFactory>(new ObjectFactory());
                return _instance;
            }

            std::unique_ptr<TreeObject> ObjectFactory::createTree(const fs::path& path) {
                return nullptr;
            }

            std::unique_ptr<BlobObject> ObjectFactory::createBlob(const fs::path filePath) {
                return nullptr;
            }
        }
    }
}