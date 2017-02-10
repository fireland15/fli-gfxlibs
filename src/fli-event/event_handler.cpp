#include "event_handler.hpp"

namespace events {
	
	unsigned int IEventHandler::nextId = 0;

	IEventHandler::IEventHandler()
		: m_id(nextId++) { }


	unsigned int IEventHandler::get_id() const { return m_id; }

	bool IEventHandler::operator==(const IEventHandler& other) {
		return this->m_id == other.m_id;
	}

	bool IEventHandler::operator!=(const IEventHandler& other) {
		return this->m_id != other.m_id;
	}

}