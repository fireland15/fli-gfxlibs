#pragma once

#include <functional>
#include <memory>

#include "event.hpp"
#include "event_sender.hpp"
#include "i_event_delegate.hpp"
#include "i_event_arguments.hpp"

namespace core {
	
	class EventDelegate : public IEventDelegate {
	public:
		/// <summary>
		/// Constructor.
		/// </summary>
		/// <param name="delegate">A function to be called when the event is being raised. The function must take a Sender and IEventArguments pointer.</param>
		EventDelegate(std::function<void(Sender, IEventArguments*)> delegate);

		/// <summary>
		/// Forwards the Sender and Event to the delegate function.
		/// </summary>
		/// <param name="sender">The sender of the event.</param>
		/// <param name="event">The event.</param>
		void operator()(Sender sender, IEventArguments* event);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="args"></param>
		virtual void SendEvent(Sender sender, IEventArguments* args);

	private:
		std::function<void(Sender, IEventArguments*)> m_delegate;

	};

}