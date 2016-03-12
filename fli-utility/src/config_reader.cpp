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

bool ConfigurationReader::Read(const std::string& key, std::string & var)
{
	return false;
}

bool ConfigurationReader::Read(const std::string & key, bool & var)
{
	auto it = m_configValues.find(key);
	if (it != m_configValues.end()) {
		std::string value = it->second;
		std::stringstream(value) >> var;
		return true;
	}
	return false;
}

bool ConfigurationReader::Read(const std::string& key, char & var)
{
	return false;
}

bool ConfigurationReader::Read(const std::string& key, unsigned char & var)
{
	return false;
}

bool ConfigurationReader::Read(const std::string& key, short & var)
{
	return false;
}

bool ConfigurationReader::Read(const std::string& key, unsigned short & var)
{
	return false;
}

bool ConfigurationReader::Read(const std::string& key, int & var)
{
	return false;
}

bool ConfigurationReader::Read(const std::string& key, unsigned int & var)
{
	return false;
}

bool ConfigurationReader::Read(const std::string& key, long & var)
{
	return false;
}

bool ConfigurationReader::Read(const std::string& key, unsigned long & var)
{
	return false;
}

bool ConfigurationReader::Read(const std::string& key, double & var)
{
	return false;
}
