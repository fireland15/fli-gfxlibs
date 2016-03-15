#pragma once

#include <string>
#include <vector>
#include <queue>

struct LogEntry {
public:
	std::string m_entry;
    std::string m_details;

	LogEntry(std::string& sender, std::string& entry, std::vector<std::string>& details);
private:
	LogEntry();
};

enum LogLvl {
    err, // Only fatal errors are logged
    wrn, // Warnings about possible problems and fatal errors are logged
    inf, // Info about application runtime state, warnings, and errors are logged
    all, // All logging events are logged
    non  // No information is logged
}

class LoggerBase {
protected:
    LogLvl m_loggingLevel;
    std::ostream m_destination;
    // Use the queue for multithreaded logging.
        //std::queue<LogEntry> m_writeQueue;
    
public:
    LoggerBase();
    ~LoggerBase();
    
    virtual void BeginLogging(std::ostream& destination, LogLvl level) = 0;
	virtual void Log() = 0;
    virtual void StopLogging() = 0;
};