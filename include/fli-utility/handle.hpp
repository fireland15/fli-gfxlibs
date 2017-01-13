#pragma once

namespace containers {

	class Handle {

	private:
		int m_value;

	public:
		Handle();

		Handle(int value);

		bool IsValid();

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

		Handle operator++();

		Handle operator++(int);

		static inline Handle Default() { return Handle(); }

	};

}