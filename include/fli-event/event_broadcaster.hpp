#pragma once

#include <map>
#include <typeindex>
#include <memory>

#include "event_queue.hpp"

namespace events {

	class EventBroadcaster {
	public:
		template <typename TEvent>
		void connect(std::function<TEvent> func) {

		}

		template <typename TEvent>
		void push(TEvent event) {

		}

	private:
		std::map<std::type_index, std::unique_ptr<IEventQueue>> m_eventQueues;
	};

}