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
					Sleep(1000);
					Clock::Duration d1 = c.TimeFromNow(t1);
					double microsecond = d1.Microseconds();
					double miliseconds = d1.Milliseconds();
					double seconds = d1.Seconds();


					Clock::Duration d2 = c.TimeFromEpoch(c.Now());
					double m2 = d2.Microseconds();
				}
			};
		}
	}
}