#include "logger_simple.hpp"

namespace logging {

	SimpleLogger::SimpleLogger(std::ostream& destination, LogLvl level) : m_target(destination), LoggerBase(level) {
		m_target << "Simple Logger Started" << std::endl;
		m_target << "\tLog Level: " << level << std::endl;
		m_target << "\tTime:      " << LogEntry::GetTimeStamp() << std::endl;
	}

	SimpleLogger::~SimpleLogger() { 
		m_target << "Simple Logger Finished" << std::endl;
		m_target << "\tTime: " << LogEntry::GetTimeStamp() << std::endl;
	}

	void SimpleLogger::Log(std::unique_ptr<LogEntry>&& entry) {
		if (entry->level <= m_loggingLevel)
			m_target << entry->ToString();
	}

}