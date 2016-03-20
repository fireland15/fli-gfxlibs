#pragma once

#include <string>
#include <sstream>
#include <ctime>

namespace fli {
	namespace util {
		namespace log {

			enum LogLvl {
				err, // Only fatal errors are logged
				wrn, // Warnings about possible problems and fatal errors are logged
				trc, // Info about entering functions is logged
				inf, // Info about application runtime state, warnings, and errors are logged
				all, // All logging events are logged
				non  // No information is logged
			};

			/// <summary>
			/// Class for storing and passing information to be logged.
			/// </summary>
			struct LogEntry {
				/// <summary>
				/// The level of logging at which this log should be written.
				/// </summary>
				LogLvl level;

				/// <summary>
				/// The module or system that wrote the log entry.
				/// </summary>
				std::string sender;

				/// <summary>
				/// The main message of the log entry.
				/// </summary>
				std::stringstream entry;

				/// <summary>
				/// Extra information to be recorded with the entry.
				/// </summary>
				std::stringstream details;

				/// <summary>
				/// Creates a string of the entry for writing to a target.
				/// </summary>
				/// <returns>String representation of entry.</returns>
				std::string ToString();

				/// <summary>
				/// Converts a LogLvl enum value to a human readable string.
				/// </summary>
				/// <param name="level"></param>
				/// <returns></returns>
				std::string ToString(LogLvl level);

				/// <summary>
				/// Creates a string representation of the current date and time.
				/// </summary>
				/// <returns></returns>
				static std::string GetTimeStamp();

				/// <summary>
				/// Formats that details of an entry so that each line appears indented to the main entry.
				/// </summary>
				/// <param name="str">The </param>
				/// <returns></returns>
				std::string FormatDetails();
			};
		}
	}
}
