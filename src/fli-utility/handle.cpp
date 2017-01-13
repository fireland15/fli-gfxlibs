#include "handle.hpp"

namespace containers {

	Handle::Handle()
		: m_value(-1) { }

	Handle::Handle(int value)
		: m_value(value) { }

	bool Handle::IsValid() {
		return m_value >= 0;
	}

	Handle Handle::operator++() {
		m_value++;
		return *this;
	}

	Handle Handle::operator++(int) {
		Handle h(m_value);
		m_value++;
		return h;
	}

}