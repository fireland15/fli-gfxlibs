#pragma once

#include <map>
#include <typeindex>
#include <memory>
#include <list>

#include "event_queue.hpp"
#include "event_handler.hpp"

namespace events {

	class EventBroadcaster {
	public:
		class EventBroadcasterBuilder;

		EventBroadcaster(std::initializer_list<IEventQueue*> queues);

		EventBroadcaster(std::list<std::unique_ptr<IEventQueue>> queues);

		template <typename TEvent>
		void connect(EventHandler<TEvent>* handler) {
			size_t typeHash = handler->get_event_type_hashcode();
			if (m_eventQueues.count(typeHash) == 0) {
				//Todo: Throw more specific exception type
				throw std::exception("Cannot connect an EventHandler for event. Event is not part of this broadcaster.");
			}

			m_eventQueues[typeHash]->connect(handler);
		}

		template <typename TEvent>
		void push(TEvent event) {
			size_t eventTypeHash = typeid(TEvent).hash_code();

			if (m_eventQueues.count(eventTypeHash) == 0) {

			}

			EventQueue<TEvent>& q = *(EventQueue<TEvent>*)m_eventQueues[eventTypeHash].get();
			q.push(event);
		}

		void flush_events() const;

		size_t queue_count() const;

	private:
		std::map<size_t, std::unique_ptr<IEventQueue>> m_eventQueues;
	};

	class EventBroadcaster::EventBroadcasterBuilder {
	public:
		EventBroadcasterBuilder();

		template <typename TEvent>
		EventBroadcasterBuilder& AddEventQueue() {
			std::unique_ptr<IEventQueue> queue(new EventQueue<TEvent>());
			m_eventQueues.push_back(std::move(queue));
			return *this;
		}

		EventBroadcaster Build();
		
	private:
		std::list<std::unique_ptr<IEventQueue>> m_eventQueues;
	};

}