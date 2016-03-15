#pragma once

#include "log_entry.hpp"

namespace fli {
	namespace util {
		namespace log {

			class LoggerBase {
			protected:
				LogLvl m_loggingLevel;
				// Use the queue for multithreaded logging.
					//std::queue<LogEntry> m_writeQueue;

			public:
				LoggerBase(LogLvl level);

				virtual void Log(LogEntry& entry) = 0;
			};

		}
	}
}
