#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "reflective/FunctionParams.h"
#include "utils/MacroUtils.h"

using namespace MaikoDev::Arc::Reflective;

#define DefineArcManager(ClassName, ClassMembers) \
CONCAT_SPACE_BETWEEN(class, ##ClassName) : public ArcManager {\
public:\
	static std::string& name();\
	static std::unique_ptr<FunctionParams> CONCAT_SPACE_BETWEEN(constructorParameters();, ##ClassMembers)\
}

namespace MaikoDev::Arc::Managers {
	class ManagerInstance;

	class ArcManager {
	public:
		ArcManager(std::unique_ptr<ManagerInstance> instance) { onManagerInit(std::move(instance)); }

		static std::unique_ptr<FunctionParams> getInitParameters(const ArcManager& manager) { 
		}
	protected:
		virtual std::unique_ptr<FunctionParams> constructorParameters() = 0;
		virtual void onManagerInit(std::unique_ptr<ManagerInstance> instance) = 0;
	};

	DefineArcManager(TestClass,
public:
	TestClass(const std::string);
	std::string getInput();
protected:

	);
}