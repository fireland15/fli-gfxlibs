#include "clock.hpp"

namespace gfx {
	namespace core {

		Clock::Timepoint::Timepoint(LARGE_INTEGER perfCount, LARGE_INTEGER frequency)
			: m_perfCount(perfCount)
			, m_frequency(frequency) { }

		Clock::Timepoint::Timepoint() { }

		Clock::Duration Clock::Timepoint::operator-(const Timepoint& rhs) {
			return Clock::Duration(rhs.m_perfCount, this->m_perfCount, m_frequency);
		}

		Clock::Duration Clock::Timepoint::operator-(const Timepoint& rhs) const {
			return Clock::Duration(rhs.m_perfCount, this->m_perfCount, m_frequency);
		}

		Clock::Duration::Duration(LARGE_INTEGER begin, LARGE_INTEGER end, LARGE_INTEGER frequency)
			: m_begin(begin)
			, m_end(end)
			, m_frequency(frequency) { }

		double Clock::Duration::Microseconds() {
			LARGE_INTEGER dif;
			dif.QuadPart = m_end.QuadPart - m_begin.QuadPart;
			return ((double)dif.QuadPart * 1000000) / m_frequency.QuadPart;
		}

		double Clock::Duration::Milliseconds() {
			LARGE_INTEGER dif;
			dif.QuadPart = m_end.QuadPart - m_begin.QuadPart;
			return ((double)dif.QuadPart * 1000) / m_frequency.QuadPart;
		}

		double Clock::Duration::Seconds() {
			LARGE_INTEGER dif;
			dif.QuadPart = m_end.QuadPart - m_begin.QuadPart;
			return (double)dif.QuadPart / m_frequency.QuadPart;
		}

		Clock::Clock() {
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			QueryPerformanceFrequency(&m_frequency);
			m_epoch = Timepoint(current, m_frequency);
		}

		Clock::Timepoint Clock::Now() {
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			return Timepoint(current, m_frequency);
		}

		Clock::Duration Clock::TimeFromNow(const Timepoint& t) {
			return Now() - t;
		}

		Clock::Duration Clock::TimeFromEpoch(const Timepoint& t) {
			return t - m_epoch;
		}

	}
}