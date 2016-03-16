#include "logger_concurrent.hpp"

namespace fli {
    namespace util {
        namespace log {
            
            ConcurrentLogger::ConcurrentLogger(std::ostream& target, LogLvl level) : SimpleLogger(m_target,level) {
				m_target << "Concurrent Logger Started" << std::endl;
				m_target << "\tLog Level: " << m_loggingLevel << std::endl;
				m_target << "\tTime:      " << LogEntry::GetTimeStamp() << std::endl;
            }
            
            ConcurrentLogger::~ConcurrentLogger() {
				m_target << "Concurrent Logger Finished" << std::endl;
				m_target << "\tTime: " << LogEntry::GetTimeStamp() << std::endl;
            }
            
            void ConcurrentLogger::Log(std::unique_ptr<LogEntry>&& entry) {
				// TODO: Add mutex locking around this.
				m_writeQueue.push(std::move(entry));

            }

			void ConcurrentLogger::Writer() {
				while (!m_writeQueue.empty()) {
					m_target << m_writeQueue.front()->ToString() << std::endl;
					m_writeQueue.pop();
				}
			}
            
        }
    }
}