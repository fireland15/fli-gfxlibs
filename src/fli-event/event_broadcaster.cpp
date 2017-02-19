#include "event_broadcaster.hpp"

namespace events {

	EventBroadcaster::EventBroadcaster(std::initializer_list<IEventQueue*> queues) {
		for (IEventQueue* queue : queues) {
			size_t eventTypeHash = queue->get_event_type_hashcode();
			std::unique_ptr<IEventQueue> pQueue(queue);

			m_eventQueues.insert(std::make_pair(eventTypeHash, std::move(pQueue)));
		}
	}

	EventBroadcaster::EventBroadcaster(std::list<std::unique_ptr<IEventQueue>> queues) {
		for (std::unique_ptr<IEventQueue>& queue : queues) {
			size_t eventTypeHash = queue->get_event_type_hashcode();

			m_eventQueues.insert(std::make_pair(eventTypeHash, std::move(queue)));
		}
	}

	void EventBroadcaster::flush_events() const {
		for (auto& p : m_eventQueues) {
			if (p.second->get_event_count() > 0) {
				p.second->flush();
			}
		}
	}

	size_t EventBroadcaster::queue_count() const {
		return m_eventQueues.size();
	}

	EventBroadcaster::EventBroadcasterBuilder::EventBroadcasterBuilder() {

	}

	EventBroadcaster EventBroadcaster::EventBroadcasterBuilder::Build() {
		return EventBroadcaster(std::move(m_eventQueues));
	}

}
