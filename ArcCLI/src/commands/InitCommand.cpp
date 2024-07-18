#include "InitCommand.h"

#include <iostream>
#include <fstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <Windows.h>
#endif

#include "io/FileUtils.h"

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            InitCommand::InitCommand(const fs::path& arcPath) : _arcPath(arcPath), _refsPath(arcPath), _objsPath(arcPath), _headPath(arcPath) {
                _refsPath.concat("\\refs");
                _objsPath.concat("\\objects");
                _headPath.concat("\\HEAD");
            }

            void InitCommand::run() {
                if (fs::exists(_arcPath)) {
                    fs::path backupPath = _arcPath;
                    backupPath.concat("\\backup");

                    /* TODO: Backup all files that due exist 
                     * You should be able to recreate 
                     * HEAD file if ref still exists
                     * not vice versa
                     */

                    std::cout << "Reinitialized empty Arc repository in " << IO::ConvertToUnixPath(_arcPath);
                }
                else {
                    fs::create_directory(_arcPath);
                    fs::create_directory(_refsPath);
                    fs::create_directory(_objsPath);

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
                    std::string arcPathStr = _arcPath.string();
                    SetFileAttributes(std::wstring(arcPathStr.begin(), arcPathStr.end()).c_str(), FILE_ATTRIBUTE_HIDDEN);
#endif

                    /* Create heads folder in refs */
                    fs::path headRefs = _refsPath;
                    headRefs.concat("\\heads");

                    fs::create_directories(headRefs);

                    /* Create HEAD file */
                    fs::path headFilePath = _arcPath;
                    headFilePath.concat("\\HEAD");

                    std::ofstream headFile(headFilePath);

                    headFile << "refs: " << IO::ConvertToUnixPath(fs::relative(headRefs, _arcPath)) << "/master";
                    headFile.close();

                    std::cout << "Initialized empty Arc repository in " << IO::ConvertToUnixPath(_arcPath);
                }
            }

            void InitCommand::undo() {

            }
        }
    }
}