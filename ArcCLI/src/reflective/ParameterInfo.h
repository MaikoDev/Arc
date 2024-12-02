#pragma once

#include <typeinfo>
#include <unordered_map>

namespace MaikoDev::Arc::Reflective {
	struct ParameterInfo {
		const std::type_info& type;

		uint32_t size;
		uint32_t startAddress;
	};

	typedef std::unordered_map<std::string, ParameterInfo> ParameterMap;
}