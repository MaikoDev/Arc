#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <memory>

#include "reflective/TypeTraits.h"

namespace MaikoDev::Arc::Memory {
	class ByteContainer {
	public:
		ByteContainer() {}
		ByteContainer(const ByteContainer& other);
		ByteContainer(const std::string& data);
		ByteContainer(const std::vector<std::byte>& data);
		ByteContainer(const void* data, const size_t size);

		~ByteContainer();

		ByteContainer& operator=(const ByteContainer& other);

		void reserve(const size_t size);

		std::unique_ptr<std::vector<std::byte>> getData();
		std::unique_ptr<std::vector<std::byte>> getData(const uint64_t startRange, const uint64_t endRange);

		template<typename ConversionType>
		static std::unique_ptr<ConversionType> ConvertData(const std::unique_ptr<std::vector<std::byte>> data) {
			if (!Reflective::isTypePrimitive<ConversionType>()) return nullptr;
			if (sizeof(ConversionType) != data->size()) return nullptr;

			auto converted = std::make_unique<ConversionType>();
			memcpy(converted.get(), data->data(), data->size());

			return converted;
		}

		template<>
		static std::unique_ptr<std::string> ConvertData(const std::unique_ptr<std::vector<std::byte>> data) {
			std::byte delimiter{ 0x0 };
			uint8_t nullCount = 0;

			for (const auto& dataByte : *data) {
				if (dataByte == delimiter) nullCount++;
			}

			switch (nullCount) {
			case 0:
				return convertToString(*data);
			case 1:
				return std::make_unique<std::string>(reinterpret_cast<char*>(data->data()));
			default:
				return nullptr;
			}
		}

		ByteContainer& append(const std::string& data);
		ByteContainer& append(const std::vector<std::byte>& data);
		ByteContainer& append(const std::byte* data, const size_t& size);
		ByteContainer& append(const void* data, const size_t& size);
		ByteContainer& append(const ByteContainer& other);

		std::unique_ptr<ByteContainer> subrange(const uint64_t startRange, const uint64_t endRange);

		const size_t& dataSize() const& { return _dataSize; }

	private:
		void expand(const size_t size);
		inline const size_t getNextAvailableSize(const size_t& dataSize);
		inline void memoryValidation(const size_t dataSize);
		inline void appendData(const void* data, const size_t size, bool isString = false);
		static std::unique_ptr<std::string> convertToString(const std::vector<std::byte>& data);
	private:
		size_t _allocatedSize = 0;
		std::byte* _dataPtr = nullptr;

		size_t _dataSize = 0;
	};
}