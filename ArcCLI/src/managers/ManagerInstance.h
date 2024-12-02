#pragma once

#include <memory>

#include "ArcManager.h"

#include "reflective/ParameterInfo.h"
#include "reflective/FunctionParams.h"

using namespace MaikoDev::Arc::Reflective;

namespace MaikoDev::Arc::Managers {
	/*class ManagerInstance {
	private:
		ManagerInstance(const )
	};*/

	class ManagerInstance {
	public:
		ManagerInstance() = delete;
		static std::unique_ptr<ManagerInstance> createInstance(const ArcManager& manager);

		template<typename DerivedManagerType>
		static std::shared_ptr<DerivedManagerType> startInstance(std::unique_ptr<ManagerInstance> instance) {
			if (!std::is_base_of<ArcManager, DerivedManagerType>::value) return nullptr;

			const std::string derivedType = typeid(DerivedManagerType).name();
			const auto instanceSearch = _instanceMap.find(derivedType);

			if (instanceSearch != _instanceMap.end()) return getManagerByDerivedType(instanceSearch->first);

			_instanceMap.insert({ derivedType, std::move(instance) });
		}
	private:
		ManagerInstance(std::unique_ptr<FunctionParams> constructorParams);

		inline std::shared_ptr<ArcManager> getManagerByDerivedType(const std::string& derivedTypeName);
	private:
		std::unique_ptr<FunctionParams> _constructorParams;

		std::unordered_map<std::string, std::unique_ptr<ManagerInstance>> _instanceMap;
		std::unordered_map<std::string, std::string> _typeManagerNameMap;
		std::unordered_map<std::string, std::shared_ptr<ArcManager>> _managerMap;
	};
}