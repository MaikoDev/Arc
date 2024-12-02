#pragma once

#include <any>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <cassert>

namespace MaikoDev::Arc::Reflective {
	class FunctionParams {
	public:
		FunctionParams();
		FunctionParams(const std::unordered_map<std::string, std::any> parameters);

		bool matches(const FunctionParams& other);

		bool registerParam(const std::string name, const std::any paramData);
		bool unregisterParam(const std::string name);

		// THROW AN EXCEPTION HERE //
		template<typename ParamType>
		const std::unique_ptr<ParamType> getParameter(const std::string name) const {
			std::unique_ptr<ParamType> parameterVal = nullptr;

			const auto& paramSearch = _paramsMapping.find(name);
			const bool isNotFound = paramSearch == _paramsMapping.end();

			if (isNotFound) return parameterVal;

			parameterVal = std::make_unique<ParamType>();
			try {
				*parameterVal = std::any_cast<ParamType>(paramSearch->second);
			}
			catch (std::bad_any_cast castEx) {
				std::printf("Requested parameter type of [%s]\ndoes not match registered type of [%s]\n", typeid(ParamType).name(), paramSearch->second.type().name());
				throw std::exception("Parameter Type mismatch!");
			}

			return parameterVal;
		}

		const size_t& totalCount() const& { return _paramsMapping.size(); }
		const std::vector<std::string> getParameterNames() const;
		const std::string& checksum() const& { return _checksum; }
	private:
		const std::string calculateChecksum();
	private:
		std::unordered_map<std::string, std::any> _paramsMapping;
		std::string _checksum;
	};
}