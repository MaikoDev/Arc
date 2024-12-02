#pragma once

#include "ArcManager.h"
#include "objects/ObjectFactory.h"

#include "reflective/ParameterInfo.h"

namespace MaikoDev::Arc::Managers {
	class ObjectManager : public ArcManager {
	public:
		static std::shared_ptr<std::unordered_map<std::string, Reflective::ParameterInfo>> parameterMapping() { return _parameterMapping; }
	private:
		ObjectManager(fs::path arcPath);
	private:
		static std::shared_ptr<std::unordered_map<std::string, Reflective::ParameterInfo>> _parameterMapping;
	};
}