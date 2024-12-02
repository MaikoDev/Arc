#include "ByteContainer.h"

namespace MaikoDev::Arc::Memory {
	ByteContainer::ByteContainer(const ByteContainer& other) : _allocatedSize(other._dataSize), _dataSize(other._dataSize) {
		_dataPtr = static_cast<std::byte*>(calloc(_allocatedSize, sizeof(std::byte)));

		memcpy(_dataPtr, other._dataPtr, _dataSize);
	}

	ByteContainer::ByteContainer(const std::string& data) : _allocatedSize(data.size() + 1), _dataSize(data.size() + 1) {
		_dataPtr = static_cast<std::byte*>(calloc(_allocatedSize, sizeof(std::byte)));

		memcpy(_dataPtr, data.data(), data.size());
	}

	ByteContainer::ByteContainer(const std::vector<std::byte>& data) : _dataSize(data.size()) {
		reserve(_dataSize);

		memcpy(_dataPtr, data.data(), _dataSize);
	}

	ByteContainer::ByteContainer(const void* data, const size_t size) {
		appendData(data, size);
	}

	ByteContainer::~ByteContainer() {
		if (_dataPtr != nullptr) free(_dataPtr);
	}

	ByteContainer& ByteContainer::operator=(const ByteContainer& other) {
		_allocatedSize = other._dataSize;
		_dataSize = _allocatedSize;

		_dataPtr = static_cast<std::byte*>(calloc(_allocatedSize, sizeof(std::byte)));

		memcpy(_dataPtr, other._dataPtr, _dataSize);

		return *this;
	}

	void ByteContainer::reserve(const size_t size) {
		if (_dataPtr != nullptr) free(_dataPtr);

		_allocatedSize = size;
		_dataPtr = static_cast<std::byte*>(calloc(_allocatedSize, sizeof(std::byte)));
	}

	std::unique_ptr<std::vector<std::byte>> ByteContainer::getData() {
		auto byteCollection = std::make_unique<std::vector<std::byte>>();
		byteCollection->reserve(_dataSize);

		for (size_t byteIndex = 0; byteIndex < _dataSize; byteIndex++) {
			byteCollection->push_back(_dataPtr[byteIndex]);
		}

		return byteCollection;
	}

	std::unique_ptr<std::vector<std::byte>> ByteContainer::getData(const uint64_t startRange, const uint64_t endRange) {
		if (startRange >= endRange) return nullptr;

		const size_t span = endRange - startRange;
		auto byteCollection = std::make_unique<std::vector<std::byte>>();
		
		byteCollection->reserve(span);
		for (size_t byteIndex = 0; byteIndex < span; byteIndex++) {
			byteCollection->push_back(_dataPtr[startRange + byteIndex]);
		}

		return byteCollection;
	}

	ByteContainer& ByteContainer::append(const std::string& data) {
		appendData(data.c_str(), data.size(), true);

		return *this;
	}

	ByteContainer& ByteContainer::append(const std::vector<std::byte>& data) {
		appendData(data.data(), data.size());

		return *this;
	}

	ByteContainer& ByteContainer::append(const std::byte* data, const size_t& size) {
		appendData(data, size);

		return *this;
	}

	ByteContainer& ByteContainer::append(const void* data, const size_t& size) {
		appendData(data, size);

		return *this;
	}

	ByteContainer& ByteContainer::append(const ByteContainer& other) {
		appendData(other._dataPtr, other._dataSize);

		return *this;
	}

	std::unique_ptr<ByteContainer> ByteContainer::subrange(const uint64_t startRange, const uint64_t endRange) {
		if (startRange >= endRange) return nullptr;

		const size_t span = endRange - startRange;
		std::byte* data = static_cast<std::byte*>(calloc(span, sizeof(std::byte)));

		memcpy(data, &_dataPtr[startRange], span);
		auto subContainer = std::make_unique<ByteContainer>(data, span);

		free(data);

		return subContainer;
	}

	void ByteContainer::expand(const size_t size) {
		_allocatedSize += size;
		void* buffer = calloc(_allocatedSize, sizeof(std::byte));

		if (_dataPtr != nullptr) {
			memcpy(buffer, _dataPtr, _dataSize);
			free(_dataPtr);
		}

		_dataPtr = static_cast<std::byte*>(buffer);
	}

	inline const size_t ByteContainer::getNextAvailableSize(const size_t& dataSize) {
		size_t availableSize = _allocatedSize;

		if (dataSize <= availableSize) return availableSize;

		do {
			availableSize *= 2;
			if (dataSize <= availableSize) break;

		} while (true);

		return availableSize;
	}

	inline void ByteContainer::memoryValidation(const size_t dataSize) {
		if (_dataPtr == nullptr) {
			reserve(dataSize);
		}
		else {
			const size_t nextSize = _dataSize + dataSize;
			const size_t requiredSize = getNextAvailableSize(nextSize);

			// We need to expand allocated memory
			if (requiredSize != _allocatedSize)
				this->expand(requiredSize - _allocatedSize);
		}
	}

	inline void ByteContainer::appendData(const void* data, const size_t size, bool isString) {
		size_t additionSize = isString ? size + 1 : size;
		memoryValidation(additionSize);

		memcpy(&_dataPtr[_dataSize], data, size);
		_dataSize += additionSize;
	}

	std::unique_ptr<std::string> ByteContainer::convertToString(const std::vector<std::byte>& data) {
		char* dataBuffer = static_cast<char*>(calloc(data.size() + 1, 1));
		memcpy(dataBuffer, data.data(), data.size());

		std::unique_ptr<std::string> converted = std::make_unique<std::string>(dataBuffer);
		free(dataBuffer);

		return converted;
	}
}