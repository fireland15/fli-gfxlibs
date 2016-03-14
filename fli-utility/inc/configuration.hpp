#pragma once

#include <map>
#include <string>
#include <sstream>

#include "config_reader_base.hpp"

class Configuration {
private:
	std::map<std::string, std::string> m_configValues;


public:
	Configuration();
	Configuration(ConfigurationReaderBase& reader);

	bool Get(const std::string& key, std::string& var);
	bool Get(const std::string& key, bool& var);
	bool Get(const std::string& key, char& var);
	bool Get(const std::string& key, unsigned char& var);
	bool Get(const std::string& key, short& var);
	bool Get(const std::string& key, unsigned short& var);
	bool Get(const std::string& key, int& var);
	bool Get(const std::string& key, unsigned int& var);
	bool Get(const std::string& key, long& var);
	bool Get(const std::string& key, unsigned long& var);
	bool Get(const std::string& key, float& var);
	bool Get(const std::string& key, double& var);
};