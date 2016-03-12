#include <string>
#include <map>

#pragma once

class ConfigurationReaderBase {
protected:
	std::map<const std::string, std::string> m_configValues;

public:
	ConfigurationReaderBase() { }
	~ConfigurationReaderBase() { }

	virtual bool Read(const std::string& key, std::string& var) = 0;
	virtual bool Read(const std::string& key, bool& var) = 0;
	virtual bool Read(const std::string& key, char& var) = 0;
	virtual bool Read(const std::string& key, unsigned char& var) = 0;
	virtual bool Read(const std::string& key, short& var) = 0;
	virtual bool Read(const std::string& key, unsigned short& var) = 0;
	virtual bool Read(const std::string& key, int& var) = 0;
	virtual bool Read(const std::string& key, unsigned int& var) = 0;
	virtual bool Read(const std::string& key, long& var) = 0;
	virtual bool Read(const std::string& key, unsigned long& var) = 0;
	virtual bool Read(const std::string& key, double& var) = 0;

protected:
	ConfigurationReaderBase(const ConfigurationReaderBase& other) : m_configValues(other.m_configValues) { }
	ConfigurationReaderBase& operator=(const ConfigurationReaderBase& other) {
		m_configValues = other.m_configValues;
		return *this;
	}

	virtual void ReadConfigValues() = 0;
};
