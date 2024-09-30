#include "BlobObject.h"

#include <fstream>
#include <string>

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            BlobObject::BlobObject(const fs::path path) : _path(path), _blobData(std::make_unique<std::string>("")) {
                _isValid = fs::exists(_path) && fs::is_regular_file(_path) && !fs::is_directory(_path);

                std::ifstream blobFile(_path);
                std::string fileLine;


                /* Read in file */
                while (std::getline(blobFile, fileLine)) {
                    _blobData->append(fileLine);
                    _blobData->append("\n");
                }

                _checksum = checksumCalculate(*_blobData);
                _blobData->clear();
            }

            void BlobObject::deserialize(const char* data) {

            }

            const std::string const& BlobObject::getChecksum() {
                if (!_isValid) return "Invalid Blob";


            }
        }
    }
}