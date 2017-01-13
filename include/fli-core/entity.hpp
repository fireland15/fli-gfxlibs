#pragma once

#include <typeindex>
#include <unordered_map>

#include <fli-utility\handle.hpp>

namespace gfx {
	namespace core {
		class Entity {
		private:
			std::unordered_map<std::type_index, containers::Handle> m_componentHandles;

		public:
			template<typename T>
			bool HasComponent() {
				return m_componentHandles.count(typeid(T)) > 0;
			}

			template<typename T>
			containers::Handle& GetComponent() {
				return m_componentHandles[typeid(T)];
			}

			template<typename T>
			void AddComponent(containers::Handle h) {
				m_componentHandles[typeid(T)] = h;
			}

			template<typename T>
			void DeleteComponent() {
				m_componentHandles.erase(typeid(T));
			}
		};
	}
}