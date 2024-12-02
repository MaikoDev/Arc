#include "FunctionParams.h"

#include <algorithm>

#include "ParameterStruct.h"
#include "utils/EncryptionUtils.h"

using namespace MaikoDev::Arc::Utils;

namespace MaikoDev::Arc::Reflective {
	FunctionParams::FunctionParams() {}
	FunctionParams::FunctionParams(const std::unordered_map<std::string, std::any> parameters) {
		for (const auto parameterNamePair : parameters) {
			_paramsMapping.insert(parameterNamePair);
		}
	}

	bool FunctionParams::matches(const FunctionParams& other) {
		if (this->totalCount()!= other.totalCount()) return false;

		return this->_checksum == other._checksum;
	}

	bool FunctionParams::registerParam(const std::string name, const std::any paramData) {
		return _paramsMapping.find(name) != _paramsMapping.end() ? false : [&]() -> bool {
			_paramsMapping.insert({ name, paramData });
			_checksum = calculateChecksum();

			return true;
		}();
	}

	bool FunctionParams::unregisterParam(const std::string name) {
		return _paramsMapping.find(name) == _paramsMapping.end() ? false : [&]() -> bool {
			_paramsMapping.erase(name);
			_checksum = calculateChecksum();

			return true;
		}();
	}

	const std::vector<std::string> FunctionParams::getParameterNames() const {
		std::vector<std::string> parameterNames;

		for (const auto& mapIter : _paramsMapping) {
			parameterNames.push_back(mapIter.first);
		}

		return parameterNames;
	}

	const std::string FunctionParams::calculateChecksum() {
		std::vector<std::pair<std::string, ParameterStruct>> structureList;
		size_t totalBytes = 0;

		for (const auto& mapIter : _paramsMapping) {
			const std::string parameterName = mapIter.first;
			const std::string parameterType = mapIter.second.type().name();

			ParameterStruct structure = { parameterName, parameterType };
			totalBytes += structure.totalSize();

			structureList.push_back({ parameterName, structure });
		}

		std::sort(structureList.begin(), structureList.end());

		ByteContainer structureData;
		const size_t parameterCount = structureList.size();

		/* Write the header */
		structureData
			.append(&parameterCount, sizeof(parameterCount))
			.append(&totalBytes, sizeof(totalBytes));

		/* Write the structures for each parameter */
		for (const auto& parameter : structureList) {
			structureData.append(*parameter.second.getStructure());
		}

		return SHA1Hash(structureData.getData());
	}
}