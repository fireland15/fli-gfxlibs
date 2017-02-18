#include "sender.hpp"

namespace events {

	Sender::Sender(void* pSender)
		: m_sender(pSender) { }

	bool Sender::operator==(const Sender& other) {
		return this->m_sender == other.m_sender;
	}

	bool Sender::operator!=(const Sender& other) {
		return this->m_sender != other.m_sender;
	}

}