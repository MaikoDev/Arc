#include "InitCommand.h"

#include <iostream>
#include <stdio.h>
#include <fstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <Windows.h>
#endif

#include "io/FileUtils.h"
#include "exceptions/CommandRuntimeException.h"

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            InitCommand::InitCommand(const fs::path& arcPath) : _arcPath(arcPath), _refsPath(arcPath), _objsPath(arcPath), _headFilePath(arcPath), _backupPath(arcPath) {
                _refsPath.concat("\\refs");
                _objsPath.concat("\\objects");
                _headFilePath.concat("\\HEAD");
                _backupPath.concat("\\backup");

                _headPtrPath = _refsPath;
                _headPtrPath.concat("\\heads");
            }

            void InitCommand::run() {
                if (fs::exists(_arcPath)) {
                    char buffer[50];

                    fs::path
                        backupObjs = _backupPath,
                        backupRefs = _backupPath,
                        backupHead = _backupPath;

                    backupRefs.concat("\\refs");
                    backupObjs.concat("\\objects");
                    backupHead.concat("\\HEAD");

                    fs::create_directory(_backupPath);

                    bool
                        objPathExist = fs::exists(_objsPath),
                        objPathEmpty = (objPathExist) ? fs::is_empty(_objsPath) : true,
                        headFileExist = fs::exists(_headFilePath),
                        headPathExist = fs::exists(_headPtrPath);

                    // Make copy of objs folder
                    if (objPathExist = fs::exists(_objsPath)) {
                        fs::rename(_objsPath, backupObjs);
                    }
                    else {
                        fs::create_directories(_objsPath);
                    }

                    if (!headPathExist) {
                        std::snprintf(buffer, sizeof(buffer),
                            "Reinitialized %s Arc repository, but was not able to recover headRefs. No Arc origin can be found!",
                            (objPathEmpty) ? "empty" : "existing"
                        );

                        throw Exceptions::CommandRuntimeException(buffer);
                    }

                    /* TODO: Backup all files that do exist 
                     * You should be able to recreate 
                     * HEAD file if ref still exists
                     * not vice versa
                     */
                    if (!headFileExist) {
                        byte count = 0;
                        fs::path headFilePath;

                        for (auto& dir : fs::directory_iterator(_headPtrPath)) {
                            if (count > 0) {
                                std::snprintf(buffer, sizeof(buffer),
                                    "Reinitialized %s Arc repository, but was not able to recover HEAD file. Multiple Arc origins found!",
                                    (objPathEmpty) ? "empty" : "existing"
                                );

                                throw Exceptions::CommandRuntimeException(buffer);
                            }

                            count++;
                            headFilePath = dir.path();
                        }

                        if (count == 0) {

                        }
                    }


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