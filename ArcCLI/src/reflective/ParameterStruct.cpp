#include "ParameterStruct.h"

namespace MaikoDev::Arc::Reflective {
	ParameterStruct::ParameterStruct(const std::string name, const std::string type) : _name(name), _type(type) {
		assignStructure(generateStructure());
	}

	ParameterStruct::ParameterStruct(const ParameterStruct& other) : _name(other._name), _type(other._type) {
		assignStructure(std::make_unique<ByteContainer>(*other._structure));
	}

	void ParameterStruct::setParameter(const std::string name, const std::string type) {
		if (name.empty() || type.empty()) return;

		_name = name;
		_type = type;

		assignStructure(generateStructure());
	}

	ParameterStruct& ParameterStruct::operator=(const ParameterStruct& other) {
		_name = other._name;
		_type = other._type;

		assignStructure(std::make_unique<ByteContainer>(*other._structure));
		return *this;
	}

	bool ParameterStruct::operator<(const ParameterStruct& other) const { return this->_name < other._name; }
	bool ParameterStruct::operator<=(const ParameterStruct& other) const { return this->_name <= other._name; }

	bool ParameterStruct::operator>(const ParameterStruct& other) const { return this->_name > other._name; }
	bool ParameterStruct::operator>=(const ParameterStruct& other) const { return this->_name >= other._name; }

	bool ParameterStruct::operator==(const ParameterStruct& other) const { return this->_name == other._name; }
	bool ParameterStruct::operator!=(const ParameterStruct& other) const { return this->_name != other._name; }

	std::unique_ptr<ByteContainer> ParameterStruct::generateStructure() {
		/* Since name and type are null terminated strings we
		   need to add the magic number 2, since those two bytes
		   represent the two null termination characters */
		const uint32_t bufferSize = _name.size() + _type.size() + 2;
		auto structure = std::make_unique<ByteContainer>(&bufferSize, sizeof(uint32_t));

		(*structure)
			.append(_name)
			.append(_type);

		return structure;
	}

	inline const void ParameterStruct::assignStructure(std::unique_ptr<ByteContainer> structure) {
		_structure = std::move(structure);

		_structureSize = *ByteContainer::ConvertData<uint32_t>(_structure->getData(0, sizeof(uint32_t)));
		_totalSize = sizeof(_structureSize) + _structureSize;
	}
}