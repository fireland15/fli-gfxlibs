#include "simple_logger.hpp"


namespace fli {
	namespace util {
		namespace config {

			SimpleLogger::SimpleLogger() : LoggerBase() { }
			SimpleLogger::~SimpleLogger() { }

			void SimpleLogger::BeginLogging(std::ostream& destination, LogLvl level) {
				LoggerBase::m_destination = destination;
				LoggerBase::m_loggingLevel = level;
			}

			void SimpleLogger::Log() {

			}

			void SimpleLogger::StopLogging() {

			}

		}
	}
}