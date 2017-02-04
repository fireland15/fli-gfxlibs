#pragma once

#include <memory>

#include "event_sender.hpp"
#include "i_event_arguments.hpp"

namespace core {

	class Event {
	public:
		Event(Sender sender, std::shared_ptr<IEventArguments> args);

	private:
		Sender m_sender;
		std::shared_ptr<IEventArguments> m_eventArgs;
	};

}