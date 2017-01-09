#include "stdafx.h"
#include "CppUnitTest.h"

#include <Clock.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fli {
	namespace gfx {
		namespace core {
			TEST_CLASS(ClockTests) {
			public:
				TEST_METHOD(TimepointSubtract) {
					Clock c;

					Clock::Timepoint t1 = c.Now();
					Clock::Timepoint t2 = c.Now();
					int x = 23231 + 343434;
					Clock::Timepoint t3 = c.Now();
					Clock::Duration d1 = c.TimeFromNow(t1);
					float microsecond = d1.Microseconds();
					float miliseconds = d1.Milliseconds();
					float seconds = d1.Seconds();


					Clock::Duration d2 = c.TimeFromEpoch(c.Now());
					float m2 = d2.Microseconds();
				}
			};
		}
	}
}