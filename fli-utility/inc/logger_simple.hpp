#include "logger_base.hpp"


namespace fli {
	namespace util {
		namespace log {
			
			/// <summary>
			/// SimpleLogger class. Single threaded loggin to an ostream derived object.
			/// </summary>
			class SimpleLogger : protected LoggerBase {
			private:
				/// <summary>
				/// Target where log entries are written to. Must be derived from std::ostream
				/// </summary>
				std::ostream& m_target;

			public:
				/// <summary>
				/// SimpleLogger Constructor. Writes beginning log statement.
				/// </summary>
				/// <param name="destination">Target to write to.</param>
				/// <param name="level">Level at which to log entries.</param>
				SimpleLogger(std::ostream& destination, LogLvl level);

				/// <summary>
				/// SimpleLogger Destructor. Writes a entry about log finishing.
				/// </summary>
				~SimpleLogger();

				/// <summary>
				/// Writes a entry to m_destination.
				/// </summary>
				/// <param name="entry">Reference to entry to write to target.</param>
				virtual void Log(LogEntry& entry);
			};

		}
	}
}
