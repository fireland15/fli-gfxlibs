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

				class Timepoint {
				private:
					LARGE_INTEGER m_perfCount;
				public:
					Timepoint() { }
					Timepoint(LARGE_INTEGER perfCount) {
						m_perfCount = perfCount;
					}

					Duration operator-(const Timepoint& rhs) {
						return Duration(*this, rhs);
					}
				};

				class Duration {
				private:
					Timepoint m_begin;
					Timepoint m_end;
				public:
					Duration(Timepoint begin, Timepoint end)
						: m_begin(begin)
						, m_end(end) { }
				};
				
			private:
				Timepoint m_epoch;
				LARGE_INTEGER m_frequency;

			public:
				Clock() {
					LARGE_INTEGER current;
					QueryPerformanceCounter(&current);
					m_epoch = Timepoint(current);

					QueryPerformanceFrequency(&m_frequency);
				}

				Timepoint Now() {
					LARGE_INTEGER current;
					QueryPerformanceCounter(&current);
					return Timepoint(current);
				}

				Duration TimeFromNow(const Timepoint& t) {

				}
			};
		}
	}
}