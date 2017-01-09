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
				Duration TimeFromEpoch(const Timepoint&);

				class Timepoint {
				private:
					LARGE_INTEGER m_perfCount;
					LARGE_INTEGER m_frequency;

					Timepoint(LARGE_INTEGER, LARGE_INTEGER);

				public:
					Timepoint();
					Duration operator-(const Timepoint&);
					Duration operator-(const Timepoint&) const;

					friend Clock::Clock();
					friend Timepoint Clock::Now();
					friend Duration Clock::TimeFromNow(const Timepoint&);
					friend Duration Clock::TimeFromEpoch(const Timepoint&);
				};

				class Duration {
				private:
					LARGE_INTEGER m_begin;
					LARGE_INTEGER m_end;
					LARGE_INTEGER m_frequency;

					Duration(LARGE_INTEGER, LARGE_INTEGER, LARGE_INTEGER);

				public:
					double Microseconds();
					double Milliseconds();
					double Seconds();

					friend Duration Timepoint::operator-(const Timepoint&);
					friend Duration Timepoint::operator-(const Timepoint&) const;
				};
				
			private:
				Timepoint m_epoch;
				LARGE_INTEGER m_frequency;
			};
		}
	}
}