#include "..\inc\config_reader.hpp"

ConfigurationReader::ConfigurationReader(const std::string filename) {
	m_filename = filename;
}

ConfigurationReader::ConfigurationReader(const ConfigurationReader & other) {

}

ConfigurationReader & ConfigurationReader::operator=(const ConfigurationReader & other) {
	// TODO: insert return statement here
	return *(new ConfigurationReader(""));
}

ConfigurationReader::~ConfigurationReader() {

}

bool ConfigurationReader::Initialize()
{
	m_configFile.open(m_filename.c_str(), std::ios::in);
	if (m_configFile.is_open()) {
		ReadConfigValues();
		m_configFile.close();
		return true;
	}
	else
		return false;
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
