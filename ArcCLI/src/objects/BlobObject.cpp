#include "BlobObject.h"
#include "ArcDefines.h"

#include <fstream>
#include <string>

#include "io/FileUtils.h"
#include "gzip/decompress.hpp"

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            BlobObject::BlobObject(const fs::path& blobPath) : _path(blobPath), _blobData(std::make_unique<std::string>("")) {
                std::unique_ptr<std::string> uncompressedData = unzipData();

                _contentSize = uncompressedData->size();
                _checksum = checksumCalculate(*uncompressedData);
            }

            BlobObject::BlobObject(const IO::StagedFile& stagedFile) : _blobData(std::make_unique<std::string>("")) {
                // This should probably throw a exception
                if (!stagedFile.isValid() || stagedFile.size() > TRACKED_FILESIZE_LIMIT) return;

                _path = stagedFile.path();
                _contentSize = stagedFile.size();
                _checksum = getBlobChecksum();

                _blobData->clear();
            }

            void BlobObject::deserialize(const char* data) {

            }

            bool BlobObject::hasDiff() {
                return false;
            }

            const std::string const& BlobObject::getChecksum() {
                //if (!_isValid) return "Invalid Blob";

                return "";
            }

            const std::string const& BlobObject::getContent() {
                return "";
            }

            std::unique_ptr<std::string> BlobObject::unzipData() {
                std::unique_ptr<std::string> blobData = IO::readFile(_path);

                //return std::make_unique<std::string>(gzip::decompress(blobData->data(), blobData->size()));
                return nullptr;
            }

            std::unique_ptr<std::string> BlobObject::getBlobChecksum() {
                std::unique_ptr<std::string> fileData = IO::readFile(_path, _contentSize);

                return checksumCalculate(*fileData);
            }
        }
    }
}