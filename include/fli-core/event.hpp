#pragma once

#include <memory>

#include "event_sender.hpp"
#include "i_event_arguments.hpp"

namespace core {

	class IEvent {
	public:
		virtual ~IEvent();

		virtual Sender GetSender();

		virtual IEventArguments* GetEventArgs();

		virtual size_t GetArgTypeHash();
	};

	class Event : public IEvent {
	public:
		/// <summary>
		/// Constructor.
		/// </summary>
		/// <param name="sender">A sender object representing the object that raised the event.</param>
		/// <param name="args">The arguments of the event. Must inherit from IEventArguments.</param>
		Event(Sender sender, IEventArguments* args);

		/// <summary>
		/// Accessor for the event sender.
		/// </summary>
		/// <returns></returns>
		virtual Sender GetSender();

		/// <summary>
		/// Get the arguments for this event.
		/// </summary>
		/// <returns>The event arguments</returns>
		virtual IEventArguments* GetEventArgs();

		/// <summary>
		/// Gets the hash code for the specific type of has code.
		/// </summary>
		/// <returns></returns>
		virtual size_t GetArgTypeHash();

	private:
		/// <summary>
		/// The arguments passed with the events.
		/// </summary>
		IEventArguments* m_args;
	};

}