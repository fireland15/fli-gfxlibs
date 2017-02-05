#pragma once

#include <map>
#include <list>
#include <typeindex>

#include "event.hpp"
#include "event_sender.hpp"
#include "event_delegate.hpp"
#include "event_handler.hpp"

namespace core {

	class EventRouter {
	public:

		EventRouter() { }

		EventRouter(const EventRouter& other) = delete;

		EventRouter& operator=(const EventRouter& other) = delete;

		EventRouter(EventRouter&& other) = delete;

		EventRouter& operator=(EventRouter&& other) = delete;

		~EventRouter() {
			for (std::pair<size_t, IEventHandler*> pair : m_eventHandlers) {
				delete pair.second;
			}
		}

		template<typename TEventArgs>
		void RegisterForEvent(EventDelegate<TEventArgs> delegate) {
			if (m_eventHandlers.count(typeid(TEventArgs).hash_code()) == 0) {
				m_eventHandlers.insert(std::make_pair(typeid(TEventArgs).hash_code(), new EventHandler<TEventArgs>));
			}

			EventHandler<TEventArgs>* pEventHandler = m_eventHandlers[typeid(TEventArgs).hash_code()];
			pEventHandler->AddDelegate(delegate);
		}

		template<typename TEventArgs>
		void RaiseEvent(Sender sender, TEventArgs args) {
			if (m_eventHandlers.count(typeid(TEventArgs).hash_code()) == 0) {
				return;
			}

			Event<TEventArgs> e(sender, args);

			EventHandler<TEventArgs>* pEventHandler = m_eventHandlers[typeid(TEventArgs).hash_code()];

			pEventHandler->DispatchEventToDelegates(e);
		}

	private:
		std::map<size_t, IEventHandler*> m_eventHandlers;

	};

}