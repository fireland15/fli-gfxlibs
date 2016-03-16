#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "logger_simple.hpp"

namespace fli {
    namespace util {
        namespace log {
            
            class ConcurrentLogger : protected SimpleLogger {
            private:
				std::queue<std::unique_ptr<LogEntry>> m_writeQueue;
				bool m_shutdown;

            public:
                ConcurrentLogger(std::ostream& target, LogLvl level);
                ~ConcurrentLogger();
                
                virtual void Log(std::unique_ptr<LogEntry>&& entry);
                
            private:
				void Writer();
            };
            
        }
    }
}