#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "logger_simple.hpp"

namespace fli {
    namespace util {
        namespace log {
            
            class ConcurrentLogger : public LoggerBase {
            private:
				std::queue<std::unique_ptr<LogEntry>> m_writeQueue;
				std::mutex m_queueMutex;
				std::condition_variable m_queueCond;

				std::atomic_flag m_shutdown;

				std::thread m_writer;

				std::ostream& m_target;

            public:
                ConcurrentLogger(std::ostream& target, LogLvl level);
                ~ConcurrentLogger();
                
                virtual void Log(std::unique_ptr<LogEntry>&& entry);
                
            private:
				void _write();
            };
            
        }
    }
}