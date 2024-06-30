#include "InitCommand.h"

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            InitCommand::InitCommand(const fs::path& arcPath) : _arcPath(arcPath) {
                fs::path absolutePath = fs::absolute(_arcPath);
                bool b = absolutePath.is_absolute();

                auto p = absolutePath.root_path();
                _refsPath = fs::relative("\\refs", absolutePath);
                _objsPath = fs::relative("\\objects", absolutePath);

                auto t = fs::absolute(_refsPath);
                t = fs::absolute(_objsPath);
                t = fs::absolute(_arcPath);
            }

            void InitCommand::run() {
                fs::create_directory(_arcPath);
                //fs::create_directory()
            }

            void InitCommand::undo() {

            }
        }
    }
}