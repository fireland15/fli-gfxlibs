#pragma once

#include "event_delegate.hpp"

namespace core {

	template<typename TEvent>
	class EventHandler {
	public:
		void AddDelegate(EventDelegate delegate);

		void operator+=(EventDelegate delegate);

	private:

	};

}