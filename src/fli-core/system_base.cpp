#include "system_base.hpp"

namespace gfx {
	namespace core {

		SystemBase::SystemBase()
			: m_pLogger(nullptr) { }

		void SystemBase::SetLogger(logging::LoggerBase* pLogger) {
			m_pLogger = pLogger;
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
}