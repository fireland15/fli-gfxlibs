#pragma once

#include <functional>
#include <queue>
#include <list>

#include "event_handler.hpp"

namespace events {

	class IEventQueue {
	public:
		virtual ~IEventQueue() { };

		virtual void connect(IEventHandler* handler) = 0;

		virtual size_t get_event_type_hashcode() const = 0;

		virtual size_t connected_count() const = 0;
	};

	template <typename TEvent>
	class EventQueue : public IEventQueue {
	public:
		EventQueue() 
			: m_eventTypeHash(typeid(TEvent).hash_code()) { };

		virtual ~EventQueue() { };

		void push(TEvent event) {
			m_events.push(event);
		}

		void connect(EventHandler<TEvent>* handler) {
			//m_handlers.count(handler);
			m_handlers.push_back(handler);
		}

		void connect(IEventHandler* handler) {
			if (handler->get_event_type_hashcode() == m_eventTypeHash) {
				connect((EventHandler<TEvent>*)handler);
			}
		}

		void flush() {
			while (!m_events.empty()) {
				TEvent e = m_events.front();
				m_events.pop();

				for (EventHandler<TEvent>* handler : m_handlers) {
					handler->invoke(e);
				}
			}
		}

		virtual size_t get_event_type_hashcode() const {
			return m_eventTypeHash;
		}

		virtual size_t connected_count() const {
			return m_handlers.size();
		}

		size_t get_event_count() const {
			return m_events.size();
		}

	private:
		std::queue<TEvent> m_events;

		std::list<EventHandler<TEvent>*> m_handlers;

		size_t m_eventTypeHash;
	};

}