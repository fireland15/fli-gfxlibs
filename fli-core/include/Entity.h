#pragma once

#include <typeindex>
#include <unordered_map>

#include <Handle.h>

namespace fli {
	namespace gfx {
		namespace core {
			class Entity {
			private:
				std::unordered_map<std::type_index, Handle> m_componentHandles;

			public:
				template<typename T>
				bool HasComponent() {
					return m_componentHandles.count(typeid(T)) > 0;
				}

				template<typename T>
				Handle& GetComponent() {
					return m_componentHandles[typeid(T)];
				}

				template<typename T>
				void AddComponent(Handle h) {
					m_componentHandles[typeid(T)] = h;
				}
			};
		}
	}
}