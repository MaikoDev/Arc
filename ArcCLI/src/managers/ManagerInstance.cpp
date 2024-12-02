#include "ManagerInstance.h"

namespace MaikoDev::Arc::Managers {
	ManagerInstance::ManagerInstance(std::unique_ptr<FunctionParams> constructorParams) : _constructorParams(std::move(constructorParams)) {
		_instanceMap.find("dasd");
		std::is_base_of<ArcManager, int>::value
	}

	std::unique_ptr<ManagerInstance> ManagerInstance::createInstance(const std::unique_ptr<FunctionParams> constructorParams) {
		return std::make_unique<ManagerInstance>(std::move(constructorParams));
	}

	std::shared_ptr<ArcManager> ManagerInstance::getManagerByDerivedType(const std::string& derivedTypeName) {
		return _managerMap.find(_typeManagerNameMap.find(derivedTypeName)->second)->second;
	}
}