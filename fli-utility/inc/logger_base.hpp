#pragma once

#include "log_entry.hpp"

namespace fli {
	namespace util {
		namespace log {

			/// <summary>
			/// An abstract class from which logging classes can derive.
			/// </summary>
			class LoggerBase {
			protected:
				/// <summary>
				/// The level above which entries are not recorded.
				/// </summary>
				LogLvl m_loggingLevel;

			public:
				/// <summary>
				/// Constructor for LoggerBase.
				/// </summary>
				/// <param name="level">The level at which entries are recorded.</param>
				LoggerBase(LogLvl level);

				/// <summary>
				/// Interface for a Log operation.
				/// </summary>
				/// <param name="entry">Reference to entry to write to target.</param>
				virtual void Log(LogEntry& entry) = 0;
			};

		}
	}
}
