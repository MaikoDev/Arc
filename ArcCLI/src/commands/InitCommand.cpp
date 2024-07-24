#include "InitCommand.h"

#include <iostream>
#include <stdio.h>
#include <fstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <Windows.h>
#endif

#define throwInitCommandException(backupObjs, backupRefs, backupHead, buffer, format, ...)\
restoreBackup(backupObjs, backupRefs, backupHead);\
throwArcCommandException(buffer, format, ...)

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
                    char buffer[255];

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
                        throwInitCommandException(
                            backupObjs, backupRefs, backupHead,
                            buffer,
                            "Reinitialized %s Arc repository, but was unable to recover headRefs. No Arc origin can be found!",
                            (objPathEmpty) ? "empty" : "existing"
                        )
                    }

                    /* TODO: Backup all files that do exist 
                     * You should be able to recreate 
                     * HEAD file if ref still exists
                     * not vice versa
                     */
                    if (!headFileExist) {
                        byte count = 0;
                        fs::path ptrFilePath;

                        for (auto& dir : fs::directory_iterator(_headPtrPath)) {
                            if (count > 0) {
                                throwInitCommandException(
                                    backupObjs, backupRefs, backupHead,
                                    buffer,
                                    "Reinitialized %s Arc repository, but was unable to recover HEAD file. Multiple Arc origins found!",
                                    (objPathEmpty) ? "empty" : "existing"
                                )
                            }

                            count++;
                            ptrFilePath = dir.path();
                        }

                         /* No Ptr can be found */
                        if (count == 0) {
                            throwInitCommandException(
                                backupObjs, backupRefs, backupHead,
                                buffer,
                                "Reinitialized %s Arc repository, but was unable to recover HEAD file. No Arc origin can be found!",
                                (objPathEmpty) ? "empty" : "existing"
                            )
                        }
                        
                        /* Rebuild the HEAD file since we have one single version origin */
                        std::ofstream headFile(_headFilePath);

                        headFile << "refs: " << IO::ConvertToUnixPath(fs::relative(ptrFilePath, _arcPath));
                        headFile.close();
                    }

                    std::cout << "Reinitialized " << ((objPathEmpty) ? "empty" : "existing") << " Arc repository in " << IO::ConvertToUnixPath(_arcPath);
                    restoreBackup(backupObjs, backupRefs, backupHead);
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
                    fs::create_directories(_headPtrPath);
                    fs::path ptrPath = _headPtrPath;
                    ptrPath.concat("\\master");

                    /* Create HEAD file */
                    std::ofstream headFile(_headFilePath);
                    std::ofstream ptrFile(ptrPath);

                    headFile << "refs: " << IO::ConvertToUnixPath(fs::relative(ptrPath, _arcPath));

                    headFile.close();
                    ptrFile.close();

                    std::cout << "Initialized empty Arc repository in " << IO::ConvertToUnixPath(_arcPath);
                }
            }

            void InitCommand::undo() {

            }

            inline void InitCommand::restoreBackup(const fs::path& objPath, const fs::path& refsPath, const fs::path& headPath) {
                if (fs::exists(objPath)) fs::rename(objPath, _objsPath);
                if (fs::exists(refsPath)) fs::rename(refsPath, _refsPath);
                if (fs::exists(headPath)) fs::rename(headPath, _headFilePath);

                fs::remove(_backupPath);
            }
        }
    }
}