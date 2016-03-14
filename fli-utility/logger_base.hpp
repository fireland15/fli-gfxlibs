#pragma once

#include <string>
#include <vector>

struct LogEntry {
public:
	std::string entry;

	LogEntry(std::string& sender, std::string& entry, std::vector<std::string>& details);
private:
	LogEntry();
};

class LoggerBase {
private:

public:
	virtual void Log();
};