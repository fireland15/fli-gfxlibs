#include "simple_logger.hpp"


namespace fli {
	namespace util {
		namespace log {

			SimpleLogger::SimpleLogger(std::ostream& destination, LogLvl level) : m_destination(destination), LoggerBase(level) {
				m_destination << "Simple Logger Started" << std::endl;
				m_destination << "\tLog Level: " << level << std::endl;
				m_destination << "\tTime:      " << LogEntry::GetTimeStamp() << std::endl;
			}

			SimpleLogger::~SimpleLogger() { 
				m_destination << "Simple Logger Finished" << std::endl;
				m_destination << "\tTime: " << LogEntry::GetTimeStamp() << std::endl;
			}

			void SimpleLogger::Log() {

			}

		}
	}
}
