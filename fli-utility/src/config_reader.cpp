#include "..\inc\config_reader.hpp"

ConfigurationReader::ConfigurationReader(std::ifstream& configFile) 
	: m_configFile(configFile) {
	ReadConfigValues();
}

ConfigurationReader::ConfigurationReader(const ConfigurationReader & other) 
	: m_configFile(other.m_configFile) {
	
}

ConfigurationReader & ConfigurationReader::operator=(const ConfigurationReader & other) {
	ConfigurationReaderBase::operator=(other);
	std::swap(m_configFile, other.m_configFile);
	return *this;
}

ConfigurationReader::~ConfigurationReader() {

}

void ConfigurationReader::ReadConfigValues()
{

}

bool ConfigurationReader::Read(std::string & var, const std::string key) {
	return false;
}

bool ConfigurationReader::Read(char & var, const std::string key) {
	return false;
}

bool ConfigurationReader::Read(unsigned char & var, const std::string key) {
	return false;
}

bool ConfigurationReader::Read(short & var, const std::string key) {
	return false;
}

bool ConfigurationReader::Read(unsigned short & var, const std::string key) {
	return false;
}

bool ConfigurationReader::Read(int & var, const std::string key) {
	return false;
}

bool ConfigurationReader::Read(unsigned int & var, const std::string key) {
	return false;
}

bool ConfigurationReader::Read(long & var, const std::string key) {
	return false;
}

bool ConfigurationReader::Read(unsigned long & var, const std::string key) {
	return false;
}

bool ConfigurationReader::Read(double & var, const std::string key) { 
	return false;
}
