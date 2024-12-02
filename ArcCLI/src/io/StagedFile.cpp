#include "StagedFile.h"

#include "io/FileUtils.h"

namespace MaikoDev::Arc::IO {
	StagedFile::StagedFile(const fs::path filePath) : _filePath(filePath) {
		_isValidFile = fs::exists(_filePath) && fs::is_regular_file(_filePath) && !fs::is_directory(_filePath);
		std::unique_ptr<std::ifstream> file = _isValidFile ? std::make_unique<std::ifstream>(_filePath) : nullptr;

		_fileSize = _isValidFile ? static_cast<uint64_t>(GetFileSize(*file)) : UINT64_MAX;
	}

	const fs::path& StagedFile::path() const& { return _filePath; }
	const uint64_t& StagedFile::size() const& { return _fileSize; }
	const bool& StagedFile::isValid() const& { return _isValidFile; }
}