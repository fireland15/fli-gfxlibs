#pragma once

#include <vector>
#include <map>
#include <functional>
#include <algorithm>

#include <Handle.h>
#include <IContainer.h>

namespace fli {
	namespace gfx {
		namespace core {
			template<typename T>
			class MisdirectContainer : public IContainerT<T> {
			private:
				std::vector<T> m_storage;
				std::map<Handle, size_t> m_handleMap;
				std::map<size_t, Handle> m_indexMap;
				Handle m_nextHandle;

			public:
				MisdirectContainer()
					: m_nextHandle(0) { }

				virtual T& Get(const Handle& handle) {
					if (m_handleMap.count(handle) == 0) {
						throw std::exception("Handle not mapped.");
					}

					size_t index = m_handleMap[handle];
					if (index >= m_storage.size()) {
						throw std::exception("Handle mapped to invalid component index");
					}

					return m_storage[index];
				}

				virtual Handle Add(T&& component) {
					size_t insertIndex = m_storage.size();
					m_storage.push_back(component);

					while (m_handleMap.count(m_nextHandle) > 0) {
						m_nextHandle++;
					}
					m_handleMap.insert(std::make_pair(m_nextHandle, insertIndex));
					m_indexMap.insert(std::make_pair(insertIndex, m_nextHandle));

					Handle retVal = m_nextHandle;
					m_nextHandle++;

					return retVal;
				}

				virtual void Remove(Handle& handle) {
					if (m_handleMap.count(handle) == 0) {
						throw std::exception("Handle not mapped");
					}

					size_t indexToDelete = m_handleMap[handle];
					size_t lastIndex = m_storage.size() - 1;

					Handle handleToLast = m_indexMap[lastIndex];

					std::iter_swap(m_storage.begin() + indexToDelete, m_storage.begin() + lastIndex);

					m_handleMap[handleToLast] = indexToDelete;
					m_indexMap[indexToDelete] = handleToLast;

					m_handleMap.erase(handle);
					m_indexMap.erase(lastIndex);

					m_storage.erase(m_storage.begin() + lastIndex);

					handle = Handle();
				}

				virtual size_t Size() {
					return m_storage.size();
				}

				virtual std::vector<Handle> GetAllHandles() {
					std::vector<Handle> handles;
					for (auto p : m_handleMap) {
						handles.push_back(p.first);
					}
					return handles;
				}

				virtual std::vector<Handle> Filter(std::function<bool(T)> predicate) {
					std::vector<Handle> handles;

					for (size_t i = 0; i < m_storage.size(); i++) {
						if (predicate(m_storage[i])) {
							handles.push_back(m_indexMap[i]);
						}
					}

					return handles;
				}
			};
		}
	}
}