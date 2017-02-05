#include "system_base.hpp"

namespace core {

	SystemBase::SystemBase(
		std::string systemName,
		std::shared_ptr<logging::LoggerBase> pLogger,
		std::shared_ptr<EventRouter> pEventRouter)
		: m_systemName(systemName)
		, m_pLogger(pLogger)
		, m_pEventRouter(pEventRouter) {

	}

	void SystemBase::Log(const std::string& msg, logging::LogLvl lvl) {
		if (m_pLogger) {
			auto log = std::unique_ptr<logging::LogEntry>(new logging::LogEntry);
			log->level = lvl;
			log->sender = m_systemName;
			log->entry << msg;
			m_pLogger->Log(std::move(log));
		}
	}

	void SystemBase::Log(const std::string& msg, const std::string& details, logging::LogLvl lvl) {
		if (m_pLogger) {
			auto log = std::unique_ptr<logging::LogEntry>(new logging::LogEntry);
			log->level = lvl;
			log->sender = m_systemName;
			log->entry << msg;
			log->details << details;
			m_pLogger->Log(std::move(log));
		}
	}

}