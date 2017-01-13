#pragma once

#include "icontainer.hpp"
#include "handle.hpp"

namespace containers {

	template<typename T>
	class IContainerT : public IContainer {

	public:
		virtual T& Get(const Handle&) = 0;
		virtual Handle Add(T) = 0;
		virtual void Remove(Handle&) = 0;
		virtual size_t Size() = 0;
		virtual std::vector<Handle> GetAllHandles() = 0;
		virtual std::vector<Handle> Filter(std::function<bool(T)>) = 0;

	};

}