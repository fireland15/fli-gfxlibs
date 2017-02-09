#pragma once

#include "event.hpp"
#include "i_event_delegate.hpp"

namespace core {

	class IEventRouter {
	public:
		virtual void RegisterForEvent(void* pSubscriber, IEventDelegate* delegate) = 0;

		virtual void RaiseEvent(IEvent* pEvent) = 0;

		virtual void IsRegisteredForEvent(void* pSubscriber) = 0;
	};

}