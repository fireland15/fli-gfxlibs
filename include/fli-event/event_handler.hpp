#pragma once

#include <functional>

#include "sender.hpp"

namespace events {

	class IEventHandler {
	private:
		const unsigned int m_id;

	public:
		static unsigned int nextId;

		IEventHandler();

		IEventHandler(const IEventHandler&);

		IEventHandler& operator=(const IEventHandler&) = delete;

		unsigned int get_id() const;

		virtual size_t get_event_type_hashcode() const = 0;

		bool operator==(const IEventHandler& other);

		bool operator!=(const IEventHandler& other);

	};

	template <typename TEvent>
	class EventHandler : public IEventHandler {
	public:
		EventHandler(std::function<void(TEvent)> callback)
			: m_callback(callback)
			, IEventHandler() { }

		void invoke(TEvent event) {
			m_callback(event);
		}
		
		virtual size_t get_event_type_hashcode() const {
			return typeid(TEvent).hash_code();
		}

		bool operator==(const EventHandler<TEvent>& other) {
			return get_id() == other.get_id();
		}

		bool operator!=(const EventHandler<TEvent>& other) {
			return get_id() != other.get_id();
		}
		
	private:
		std::function<void(TEvent)> m_callback;
	};

}