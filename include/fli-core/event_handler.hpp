#pragma once

#include <list>
#include <type_traits>

#include "event_delegate.hpp"

namespace core {

	class IEventHandler {

	};

	template<class TEventArgs>
	class EventHandler : public IEventHandler {
	public:

		/*************************************************************
		* Event Dispatch Methods
		**************************************************************/

		/// <summary>
		/// Calls each delegate's operator() method with the event parameters.
		/// </summary>
		void DispatchEventToDelegates(Event<TEventArgs> e) {
			for (auto delegate : m_delegates) {
				delegate(e.Sender, e.Args);
			}
		}

		/*************************************************************
		* Delegate Add/Remove Methods
		**************************************************************/

		/// <summary>
		/// Subscribes an object to this event handler.
		/// </summary>
		/// <param name="delegate">A delegate to be called when this event handlers event is raised.</param>
		void AddDelegate(EventDelegate<TEventArgs> delegate) {
			m_delegates.push_back(delegate);
		}
		
		/// <summary>
		/// Subscribes an object to this event handler.
		/// </summary>
		/// <param name="delegate">A delegate to be called when this event handlers event is raised.</param>
		void operator+=(EventDelegate<TEventArgs> delegate) {
			m_delegates.push_back(delegate);
		}

		/// <summary>
		/// Unsubscribes an object from this event handler.
		/// </summary>
		/// <param name="delegate">The delegate to remove from this handler.</param>
		void RemoveDelegate(EventDelegate<TEventArgs> delegate) {
			throw std::exception("Not implemented");
		}

		/// <summary>
		/// Unsubscribes an object from this event handler.
		/// </summary>
		/// <param name="delegate">The delegate to remove from this handler.</param>
		void operator-=(EventDelegate<TEventArgs> delegate) {
			throw std::exception("Not implemented");
		}

	private:
		std::list<EventDelegate<TEventArgs>> m_delegates;

	};

}