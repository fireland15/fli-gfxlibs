#pragma once

#include <Handle.h>

namespace fli {
	namespace gfx {
		namespace core {
			template<typename T>
			class IContainer {
			public:
				virtual T& Get(const Handle&) = 0;
				virtual Handle Add(T) = 0;
				virtual void Remove(Handle&) = 0;
				virtual size_t Size() = 0;
				virtual std::vector<Handle> GetAllHandles() = 0;
				virtual std::vector<Handle> Filter(std::function<bool(T)>) = 0;
			};
		}
	}
}