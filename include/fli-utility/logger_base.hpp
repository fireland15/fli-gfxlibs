#pragma once

#include <memory>

#include "log_entry.hpp"

namespace logging {

	/// <summary>
	/// An abstract class from which logging classes can derive.
	/// </summary>
	class LoggerBase {
	protected:
		/// <summary>
		/// The level above which entries are not recorded.
		/// </summary>
		LogLvl m_loggingLevel;

	public:
		/// <summary>
		/// Constructor for LoggerBase.
		/// </summary>
		/// <param name="level">The level at which entries are recorded.</param>
		LoggerBase(LogLvl level);

		/// <summary>
		/// Interface for a Log operation.
		/// </summary>
		/// <param name="entry">unique ptr</param>
		virtual void Log(std::unique_ptr<LogEntry>&& entry) = 0;
	};
}
