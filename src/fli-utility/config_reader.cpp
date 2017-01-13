#include "config_reader.hpp"

namespace config {

	ConfigurationReader::ConfigurationReader(std::ifstream& configFile)
		: m_configFile(configFile) {

	}

	std::map<std::string, std::string> ConfigurationReader::GetConfigValues()
	{
		std::map<std::string, std::string> configValues;
		if (m_configFile.is_open()) {
			std::string line;
			while (std::getline(m_configFile, line)) {
				size_t pos = line.find('=');
				std::string key = line.substr(0, pos);
				std::string value = line.substr(pos + 1);
				configValues[key] = value;
			}
		}
		return configValues;
	}
}
