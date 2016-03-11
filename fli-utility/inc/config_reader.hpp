#include <fstream>
#include <string>
#include <map>

#pragma once

class ConfigurationReader {
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
	std::ifstream m_configFile;
	std::string m_filename;
	std::map<std::string, std::string> m_configValues;

/******** Public Methods ********/
public:
	ConfigurationReader(const std::string filename);
	ConfigurationReader(const ConfigurationReader& other);
	ConfigurationReader &operator=(const ConfigurationReader &other);
	~ConfigurationReader();

	bool Initialize();

/******** Private Methods ********/
private:
	void ReadConfigValues();
};