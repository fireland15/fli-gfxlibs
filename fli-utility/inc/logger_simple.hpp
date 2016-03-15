#include "logger_base.hpp"


namespace fli {
	namespace util {
		namespace log {
			
			class SimpleLogger : protected LoggerBase {
			private:
				std::ostream& m_destination;

			public:
				SimpleLogger(std::ostream& destination, LogLvl level);
				~SimpleLogger();

				virtual void Log();
			};

		}
	}
}
