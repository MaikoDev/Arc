#include "FilePath.h"

namespace MaikoDev {
    namespace Arc {
        namespace IO {
            const FilePath FilePath::_workDir(FS::current_path());
            const FilePath& FilePath::getWorkingDir() { return _workDir; }

            FilePath::FilePath() {

            }

            FilePath::FilePath(const char* basePath) {
                
            }

            FilePath::FilePath(const FS::path& basePath) {

            }

            const std::unique_ptr<FilePath> FilePath::getRelative(const char* relativePath) const {

            }

            const std::unique_ptr<FilePath> FilePath::getParent() const {

            }

            const FS::path FilePath::getAbsolute() const {

            }

            const bool FilePath::isBasePath() const {

            }
        }
    }
}