#pragma once

#define WIN32_LEAN_AND_MEAN

#include <chrono>
#include <Windows.h>

namespace fli {
	namespace gfx {
		namespace core {
			class Clock {
			public:
				class Duration;
				class Timepoint;

				Clock();
				Timepoint Now();
				Duration TimeFromNow(const Timepoint&);

				class Timepoint {
				private:
					LARGE_INTEGER m_perfCount;
					LARGE_INTEGER m_frequency;

					Timepoint(LARGE_INTEGER perfCount, LARGE_INTEGER frequency)
						: m_perfCount(perfCount)
						, m_frequency(frequency) { }
				public:
					Timepoint() { }
					
					Duration operator-(const Timepoint& rhs) {
						return Duration(rhs.m_perfCount, this->m_perfCount, m_frequency);
					}

					friend Clock::Clock();
					friend Timepoint Clock::Now();
					friend Duration Clock::TimeFromNow(const Timepoint&);
				};

				class Duration {
				private:
					LARGE_INTEGER m_begin;
					LARGE_INTEGER m_end;
					LARGE_INTEGER m_frequency;

					Duration(LARGE_INTEGER begin, LARGE_INTEGER end, LARGE_INTEGER frequency)
						: m_begin(begin)
						, m_end(end)
						, m_frequency(frequency) { }
				public:
					int Microseconds() {
						LARGE_INTEGER dif;
						dif.QuadPart = m_end.QuadPart - m_begin.QuadPart;
						return (dif.QuadPart * 1000000) / m_frequency.QuadPart;
					}

					int Milliseconds() {
						LARGE_INTEGER dif;
						dif.QuadPart = m_end.QuadPart - m_begin.QuadPart;
						dif.QuadPart *= 1000;
						dif.QuadPart /= m_frequency.QuadPart;
						return dif.QuadPart;
					}

					float Seconds() {
						LARGE_INTEGER dif;
						dif.QuadPart = m_end.QuadPart - m_begin.QuadPart;
						return dif.QuadPart / m_frequency.QuadPart;
					}

					friend Duration Timepoint::operator-(const Timepoint&);
				};
				
			private:
				Timepoint m_epoch;
				LARGE_INTEGER m_frequency;

			public:
			};

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
		}
	}
}