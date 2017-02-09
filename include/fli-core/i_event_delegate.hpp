#pragma once

#include "event.hpp"
#include "event_sender.hpp"

namespace core {

	class IEventDelegate {
	public:
		virtual void operator()(Sender sender, IEventArguments* args) = 0;

		virtual void SendEvent(Sender sender, IEventArguments* args) = 0;
	};

}