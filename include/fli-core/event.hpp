#pragma once

#include <memory>

#include "event_sender.hpp"
#include "i_event_arguments.hpp"

namespace core {

	template <typename TEventArgs>
	struct Event {
	public:
		/// <summary>
		/// Constructor.
		/// </summary>
		/// <param name="sender">A sender object representing the object that raised the event.</param>
		/// <param name="args">The arguments of the event. Must inherit from IEventArguments.</param>
		Event(Sender sender, TEventArgs args);

		Sender Sender;
		TEventArgs Args;
	};

}