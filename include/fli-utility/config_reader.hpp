#include <fstream>
#include <string>
#include <map>
#include <sstream>

#include "config_reader_base.hpp"

#pragma once

namespace config {

	/// <summary>
	/// Class for reading configuration values from a simple text file of key=value pairs of configuration values.
	/// </summary>
	class ConfigurationReader : public ConfigurationReaderBase {
	private:
		/// <summary>
		/// The file from which configuration values are be read.
		/// </summary>
		std::ifstream& m_configFile;

	public:
		/// <summary>
		/// Constructor which sets the file stream from which to read values from.
		/// </summary>
		/// <param name="configFile">Configuration file to read configuration values from.</param>
		ConfigurationReader(std::ifstream& configFile);

		/// <summary>
		/// Reads configuration values from m_configFile stream, building a std::map of keys and values
		/// </summary>
		/// <returns>std::map of values and their keys</returns>
		virtual std::map<std::string, std::string> GetConfigValues();
	};
}