#include <fstream>
#include <string>
#include <map>
#include <sstream>

#include "config_reader_base.hpp"

#pragma once

class ConfigurationReader : protected ConfigurationReaderBase {
/******** Public Members ********/
public:
	virtual bool Read(const std::string& key, std::string& var);
	virtual bool Read(const std::string& key, bool& var);
	virtual bool Read(const std::string& key, char& var);
	virtual bool Read(const std::string& key, unsigned char& var);
	virtual bool Read(const std::string& key, short& var);
	virtual bool Read(const std::string& key, unsigned short& var);
	virtual bool Read(const std::string& key, int& var);
	virtual bool Read(const std::string& key, unsigned int& var);
	virtual bool Read(const std::string& key, long& var);
	virtual bool Read(const std::string& key, unsigned long& var);
	virtual bool Read(const std::string& key, double& var);

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