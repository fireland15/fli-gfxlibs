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
                
            public:
                ConcurrentLogger(std::ostream& target, LogLvl level);
                ~SimpleLConcurrentLoggeroggerMT();
                
                virtual void Log(LogEntry& entry);
            };
            
        }
    }
}