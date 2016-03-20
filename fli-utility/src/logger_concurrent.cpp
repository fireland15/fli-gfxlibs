#include "logger_concurrent.hpp"

namespace fli {
    namespace util {
        namespace log {
            
            ConcurrentLogger::ConcurrentLogger(std::ostream& target, LogLvl level) : m_target(target), LoggerBase(level) {
				m_target << "Concurrent Logger Started" << std::endl;
				m_target << "\tLog Level: " << m_loggingLevel << std::endl;
				m_target << "\tTime:      " << LogEntry::GetTimeStamp() << std::endl;

				m_shutdown.test_and_set();
				m_writer = std::thread(&ConcurrentLogger::_write, this);
            }
            
            ConcurrentLogger::~ConcurrentLogger() {
				//m_target << "here1" << std::endl;
				m_shutdown.clear();
				m_queueCond.notify_one();
				//m_target << "here2" << std::endl;
				m_writer.join();

				while (!m_writeQueue.empty()) {
					m_target << "finishing" << std::endl;
					std::unique_ptr<LogEntry> p = std::move(m_writeQueue.front());
					m_writeQueue.pop();
					m_target << p->ToString();
				}

				m_target << "Concurrent Logger Finished" << std::endl;
				m_target << "\tTime: " << LogEntry::GetTimeStamp() << std::endl;
            }
            
            void ConcurrentLogger::Log(std::unique_ptr<LogEntry>&& entry) {
				std::unique_lock<std::mutex> lock(m_queueMutex);
				m_writeQueue.push(std::move(entry));
				lock.unlock();
				m_queueCond.notify_one();
            }

			void ConcurrentLogger::_write() {
				while (m_shutdown.test_and_set()) {
					std::unique_lock<std::mutex> lock(m_queueMutex);

					while (m_writeQueue.empty()) {
						m_queueCond.wait(lock);
						if (!m_shutdown.test_and_set())
							return;
					}

					while (!m_writeQueue.empty()) {
						std::unique_ptr<LogEntry> p = std::move(m_writeQueue.front());
						m_writeQueue.pop();
						m_target << p->ToString();
					}
				}
			}
            
        }
    }
}