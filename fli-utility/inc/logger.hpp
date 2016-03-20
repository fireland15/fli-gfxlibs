#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>

#pragma once

enum DbgLevel {
	none,
	err,
	warn,
	info,
	debug1,
};

#ifdef _DEBUG
#define LOG(level, poster, msg) Logger::Instance()->Write(level, poster, msg)
#else
#define LOG(level, poster, msg)
#endif // LOGGING

class Logger {
	/******** Public Members ********/
public:

	/******** Private Members ********/
private:
	static Logger* m_pLogger;
	static std::ofstream m_fs;
	DbgLevel m_debugLevel;

	/******** Public Methods ********/
public:
	/// <summary>
	/// Gets the Logger instance. The Instance is used application wide.
	/// </summary>
	/// <returns>Returns reference to a Logger object.</returns>
	static Logger* Instance();

	~Logger();

	/// <summary>
	/// Opens the log file. Must be called before writing to log.
	/// </summary>
	/// <param name="filename">Name of file to open.</param>
	/// <returns>True if file opened.</returns>
	bool Open(const std::string& filename);

	/// <summary>
	/// Sets the level of logs that are recorded
	/// </summary>
	/// <param name="debugLevel"></param>
	void SetLoggingLevel(DbgLevel debugLevel);

	/// <summary>
	/// Writes a message to the log. Includes timestamp and an identifier for who/what posted the log.
	/// </summary>
	/// <param name="debugLevel">The logging level of this log. If lower than the currently defined logging level, the log is not recorded.</param>
	/// <param name="poster">The unit, object, or thing that is reporting the log entry.</param>
	/// <param name="msg">The message to be posted to the logfile</param>
	void Write(const DbgLevel debugLevel, const std::string& poster, const std::string& msg);
	
	/// <summary>
	/// Closes the log file.
	/// </summary>
	void Close();
	
	/******** Private Methods ********/
private:
	Logger();
	Logger(const Logger& other);
	Logger &operator=(const Logger &other);

	/// <summary>
	/// Gets the current time in a string format
	/// </summary>
	/// <returns>Current time in format: Www Mmm dd hh:mm:ss yyyy</returns>
	std::string timeStamp();
};