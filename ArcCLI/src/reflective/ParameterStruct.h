#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include "memory/ByteContainer.h"

using namespace MaikoDev::Arc::Memory;

namespace MaikoDev::Arc::Reflective {
	class ParameterStruct {
	public:
		ParameterStruct() {};
		ParameterStruct(const std::string name, const std::string type);
		ParameterStruct(const ParameterStruct& other);

		void setParameter(const std::string name, const std::string type);

		std::unique_ptr<std::vector<std::byte>> getStructure() const { return _structure->getData(); }

		const uint32_t& structureSize() const& { return _structureSize; }
		const uint32_t& totalSize() const& { return _totalSize; }

		ParameterStruct& operator=(const ParameterStruct& other);

		bool operator<(const ParameterStruct& other) const;
		bool operator<=(const ParameterStruct& other) const;

		bool operator>(const ParameterStruct& other) const;
		bool operator>=(const ParameterStruct& other) const;

		bool operator==(const ParameterStruct& other) const;
		bool operator!=(const ParameterStruct& other) const;
	private:
		std::unique_ptr<ByteContainer> generateStructure();
		inline const void assignStructure(std::unique_ptr<ByteContainer> structure);
	private:
		std::string _name;
		std::string _type;

		std::unique_ptr<ByteContainer> _structure;

		uint32_t _structureSize = 0;
		uint32_t _totalSize = 0;
	};
}