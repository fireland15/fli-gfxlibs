#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <conditional_variable>

#include "logger_base.hpp"

namespace fli {
    namespace util {
        namespace log {
            
            class ConcurrentLogger : protected SimpleLogger {
            private:
                std::queue<LogEntry*>
            public:
                ConcurrentLogger(std::ostream& target, LogLvl level);
                ~SimpleLConcurrentLoggeroggerMT();
                
                virtual void Log(LogEntry& entry);
                void Log(LogEntry* entry);
                
            private:
                void Writer() {
                    
                }
            };
            
        }
    }
}