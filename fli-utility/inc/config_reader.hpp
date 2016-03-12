#include <fstream>
#include <string>
#include <map>

#include "config_reader_base.hpp"

#pragma once

class ConfigurationReader : protected ConfigurationReaderBase {
/******** Public Members ********/
public:
	bool Read(std::string& var, const std::string key);
	bool Read(char& var, const std::string key);
	bool Read(unsigned char& var, const std::string key);
	bool Read(short& var, const std::string key);
	bool Read(unsigned short& var, const std::string key);
	bool Read(int& var, const std::string key);
	bool Read(unsigned int& var, const std::string key);
	bool Read(long& var, const std::string key);
	bool Read(unsigned long& var, const std::string key);
	bool Read(double& var, const std::string key);

/******** Private Members ********/
private:
	std::ifstream& m_configFile;

/******** Public Methods ********/
public:
	ConfigurationReader(std::ifstream& configFile);
	ConfigurationReader(const ConfigurationReader& other);
	ConfigurationReader &operator=(const ConfigurationReader &other);
	~ConfigurationReader();

/******** Private Methods ********/
private:
	void ReadConfigValues();
};