#pragma once

namespace fli {
	namespace gfx {
		namespace core {
			class Handle {
			private:
				int m_value;

			public:
				Handle()
					: m_value(-1) { }

				Handle(int value)
					: m_value(value) { }

				bool IsValid() {
					return m_value >= 0;
				}

				inline bool operator==(const Handle rhs) const {
					return m_value == rhs.m_value;
				}

				inline bool operator!=(const Handle rhs) const {
					return m_value != rhs.m_value;
				}

				inline bool operator>(const Handle rhs) const {
					return m_value > rhs.m_value;
				}

				inline bool operator<(const Handle rhs) const {
					return m_value < rhs.m_value;
				}

				Handle operator++() {
					m_value++;
					return *this;
				}

				Handle operator++(int) {
					Handle h(m_value);
					m_value++;
					return h;
				}
			};
		}
	}
}