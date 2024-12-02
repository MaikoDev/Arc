#pragma once

#include "ByteStack.h"

#include "utils/MacroUtils.h"
#include "reflective/TypeTraits.h"

#define CREATE_BYTE_CONVERSION_METHOD(ConversionType, MethodDefinition) \
template<> \
const inline UniqueByteStack ToByteStack<##ConversionType>(CONCAT_SPACE_BETWEEN(const, ##ConversionType) data) ##MethodDefinition

namespace MaikoDev::Arc::Memory {
	template <typename DataType>
	const inline UniqueByteStack ToByteStack(const DataType data) {
		if (!Reflective::isTypePrimitive(data) || std::is_void_v<DataType>) return nullptr;

		const size_t dataSize = sizeof(DataType);
		UniqueByteStack dataStack = std::make_unique<ByteStackType>();
		
		for (unsigned long long byteIndex = 0; byteIndex < dataSize; byteIndex++) {
			std::byte currentByte = static_cast<std::byte>(2);
		}

		return nullptr;
	}

	CREATE_BYTE_CONVERSION_METHOD(bool, 
		{
			if (!Reflective::isTypePrimitive(data) || std::is_void_v<int>) return nullptr;

			const size_t dataSize = sizeof(int);
			UniqueByteStack dataStack = std::make_unique<ByteStackType>();

			for (unsigned long long byteIndex = 0; byteIndex < dataSize; byteIndex++) {
				std::byte currentByte = static_cast<std::byte>(2);
			}

			return nullptr;
		}
	);
}