#pragma once

#include <map>
#include <list>
#include <set>
#include <memory>
#include <exception>
#include <typeindex>

#include "event.hpp"
#include "event_sender.hpp"
#include "event_delegate.hpp"
#include "event_handler.hpp"

namespace core {

	class EventRouter {
	private:
		bool IsRegisteredForEvent(size_t typeHash, void* pSubscriber);

	public:

		EventRouter() = default;

		EventRouter(const EventRouter& other) = delete;

		EventRouter& operator=(const EventRouter& other) = delete;

		EventRouter(EventRouter&& other) = delete;

		EventRouter& operator=(EventRouter&& other) = delete;

		~EventRouter() = default;

		template<typename TEventArgs>
		void RegisterForEvent(void* pSubscriber, EventDelegate<TEventArgs> delegate) {
			size_t typeHash = typeid(TEventArgs).hash_code();

			// Check if subscriber is already subscribed to event.
			if (IsRegisteredForEvent(typeHash, pSubscriber)) {
				throw std::exception("Already subscriber to event");
			}
			
			// Create new event handler if it doesn't exist.
			if (m_eventHandlers.count(typeHash) == 0) {
				std::unique_ptr<IEventHandler> pEventHandler = std::unique_ptr<IEventHandler>(new EventHandler<TEventArgs>);
				m_eventHandlers.insert(std::move(std::make_pair(typeHash, std::move(pEventHandler))));
			}

			// Add delegate to event handler
			EventHandler<TEventArgs>* pEventHandler = m_eventHandlers[typeHash];
			pEventHandler->AddDelegate(delegate);
		}

		template<typename TEventArgs>
		bool IsRegisteredForEvent(void* pSubscriber) {
			size_t typeHash = typeid(TEventArgs).hash_code();


		}

		template<typename TEventArgs>
		void RaiseEvent(Sender sender, TEventArgs args) {
			size_t typeHash = typeid(TEventArgs).hash_code();
			if (m_eventHandlers.count(typeHash) == 0) {
				return;
			}

			Event<TEventArgs> e(sender, args);

			EventHandler<TEventArgs>* pEventHandler = m_eventHandlers[typeHash];

			pEventHandler->DispatchEventToDelegates(e);
		}

	private:
		std::map<size_t, std::unique_ptr<IEventHandler>> m_eventHandlers;

		std::map<size_t, std::set<void*>> m_eventSubscribers;

	};

}