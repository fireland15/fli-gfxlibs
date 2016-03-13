#include <fstream>
#include <string>
#include <map>
#include <sstream>

#include "config_reader_base.hpp"

#pragma once

class ConfigurationReader : public ConfigurationReaderBase {
private:
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