#include "AddCommand.h"

#include "objects/BlobObject.h"

using namespace MaikoDev::Arc::Objects;

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            AddCommand::AddCommand(const fs::path filePath) {
                if (fs::is_directory(filePath)) return;

                _filePaths.push_back(filePath);
            }

            AddCommand::AddCommand(const std::vector<fs::path> filePaths) {
                for (const auto& filePath : filePaths) {
                    if (fs::is_directory(filePath)) continue;

                    _filePaths.push_back(filePath);
                }
            }

            void AddCommand::run() {
                /*for (const auto& filePath : _filePaths) {
                    BlobObject fileObj(filePath);
                }*/
            }
        }
    }
}