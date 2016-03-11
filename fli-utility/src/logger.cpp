#include "../inc/logger.hpp"

Logger* Logger::m_pLogger = nullptr;
std::ofstream Logger::m_fs;

Logger::Logger() {
	// TODO: Implement me
}

Logger::Logger(const Logger& other) {
	// TODO: Implement me
}

Logger &Logger::operator=(const Logger &other) {
	return *this;
}

Logger::~Logger() {
	if(m_fs.is_open())
		m_fs.close();
}

Logger* Logger::Instance() {
	if (m_pLogger == nullptr) {
		m_pLogger = new Logger();
	}
	return m_pLogger;
}

bool Logger::Open(const std::string& filename) {
	if (filename.empty())
		return false;

	m_fs.open(filename);

	if (m_fs.is_open())
		return true;
	return false;
}

void Logger::SetLoggingLevel(DbgLevel debugLevel) {
	m_debugLevel = debugLevel;
}

void Logger::Write(const DbgLevel debugLevel, const std::string& poster, const std::string& msg) {
	if (debugLevel <= m_debugLevel) {
		std::string str = "[" + poster.substr(0, 6) + "]";
		m_fs << timeStamp() << " " << std::setw(8) << std::left << str << " " << msg << std::endl;
	}
}

std::string Logger::timeStamp() {
	time_t rawtime;
	tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	char buf[26];
	asctime_s(buf, 26, &timeinfo);
	buf[24] = '\0';
	return std::string(buf);
}

void Logger::Close() {
	if (m_fs.is_open())
		m_fs.close();
}