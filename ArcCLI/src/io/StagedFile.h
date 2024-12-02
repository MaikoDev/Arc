#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace MaikoDev::Arc::IO {
	class StagedFile {
	public:
		StagedFile(const fs::path filePath);

		const fs::path& path() const&;
		const uint64_t& size() const&;
		const bool& isValid() const&;
	private:
		fs::path _filePath;
		uint64_t _fileSize;

		bool _isValidFile = false;
	};
}