#pragma once

#include <filesystem>

#include <commands/ICommand.h>

namespace fs = std::filesystem;

namespace MaikoDev {
    namespace Arc{
        namespace Commands {
            class InitCommand : public ICommand {
            public:
                InitCommand(const fs::path& arcPath);

                virtual void run() override;
                virtual void undo() override;
            private:
                const fs::path& _arcPath;
                fs::path _refsPath;
                fs::path _objsPath;
                fs::path _headFilePath;
                fs::path _headPtrPath;
                fs::path _backupPath;
            };
        }
    }
}