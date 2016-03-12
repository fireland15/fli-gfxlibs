#include <string>
#include <map>

#pragma once

class ConfigurationReaderBase {
protected:
	std::map<const std::string, std::string> m_configValues;

public:
	ConfigurationReaderBase() { }
	~ConfigurationReaderBase() { }

	virtual bool Read(std::string& var, const std::string key) = 0;
	virtual bool Read(char& var, const std::string key) = 0;
	virtual bool Read(unsigned char& var, const std::string key) = 0;
	virtual bool Read(short& var, const std::string key) = 0;
	virtual bool Read(unsigned short& var, const std::string key) = 0;
	virtual bool Read(int& var, const std::string key) = 0;
	virtual bool Read(unsigned int& var, const std::string key) = 0;
	virtual bool Read(long& var, const std::string key) = 0;
	virtual bool Read(unsigned long& var, const std::string key) = 0;
	virtual bool Read(double& var, const std::string key) = 0;

protected:
	ConfigurationReaderBase(const ConfigurationReaderBase& other) : m_configValues(other.m_configValues) { }
	ConfigurationReaderBase& operator=(const ConfigurationReaderBase& other) {
		m_configValues = other.m_configValues;
		return *this;
	}

	virtual void ReadConfigValues() = 0;
};
