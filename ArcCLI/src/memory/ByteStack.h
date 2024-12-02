#pragma once

#include <vector>
#include <stack>
#include <typeinfo>
#include <memory>

namespace MaikoDev::Arc::Memory {
	typedef std::stack<std::byte, std::vector<std::byte>> ByteStackType;
	typedef std::unique_ptr<std::stack<std::byte, std::vector<std::byte>>> UniqueByteStack;

	class ByteStack {
	public:
		template<typename DataType>
		static std::unique_ptr<ByteStack> ConvertFrom(const DataType type) {
			const size_t dataSize = sizeof(DataType);
			const void* const ptr = calloc(dataSize, 1);

			memcpy(ptr, &type, sizeof(DataType))

			return std::make_unique<ByteStack>(typeid(DataType), dataSize, ptr);
		}

		template<typename DataType>
		static DataType ConvertTo() {

		}
	private:
		ByteStack(const std::type_info& type, const size_t size, const void* const ptr) : _dataType(type), _dataSize(size), _dataPtr(ptr) {
			
		}
	private:
		const std::type_info& _dataType;
		const size_t _dataSize;

		const void* const _dataPtr;
	};
}