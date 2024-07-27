#include "TrackedObject.h"

#include <iomanip>
#include <memory>

using namespace MaikoDev::Arc::Objects;

std::string const TrackedObject::serialize() { return getContent(); }

std::unique_ptr<std::string> TrackedObject::checksumCalculate(const std::string& input) {
    SHA256((unsigned char*)input.c_str(), input.length(), _checksumHash);

    for (unsigned int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        _stringBuilder << std::setfill('0') << std::setw(2) << std::hex << (int)_checksumHash[i];
    }

    std::unique_ptr<std::string> checksum = std::make_unique<std::string>(_stringBuilder.str());
    _stringBuilder.clear();

    return checksum;
}