#pragma once

#include <functional>
#include <memory>

#include "event.hpp"
#include "event_sender.hpp"
#include "i_event_arguments.hpp"

namespace core {
	
	template <typename TEventArgs>
	class EventDelegate {
	public:
		/// <summary>
		/// Constructor.
		/// </summary>
		/// <param name="delegate">A function to be called when the event is being raised. The function must take a Sender and IEventArguments pointer.</param>
		EventDelegate(std::function<void(Sender, TEventArgs)> delegate);

		/// <summary>
		/// Forwards the Sender and Event to the delegate function.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="event">The event.</param>
		void operator()(Sender sender, Event event);

	private:
		std::function<void(Sender, TEventArgs)> m_delegate;

	};

}