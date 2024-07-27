#include "BlobObject.h"

#include <fstream>
#include <string>

namespace MaikoDev {
    namespace Arc {
        namespace Objects {
            BlobObject::BlobObject(const fs::path path) : _path(path), _blobData(std::make_unique<std::string>("")) {
                std::ifstream blobFile(_path);
                std::string fileLine;

                /* Read in file */
                while (std::getline(blobFile, fileLine)) {
                    _blobData->append(fileLine);
                    _blobData->append("\n");
                }

                _checksum = checksumCalculate(*_blobData);
            }

            void BlobObject::deserialize(const char* data) {

            }
        }
    }
}