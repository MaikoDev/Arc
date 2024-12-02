#pragma once

#include <type_traits>

namespace MaikoDev::Arc::Reflective {
	template <typename ObjectType>
	const inline bool isTypePrimitive(const ObjectType&) {
		return std::is_fundamental_v<ObjectType>;
	}

	template <typename ObjectType>
	const inline bool isTypePrimitive() {
		return std::is_fundamental_v<ObjectType>;
	}
}