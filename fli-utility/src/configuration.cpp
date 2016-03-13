#include "configuration.hpp"

Configuration::Configuration() {

}

Configuration::Configuration(ConfigurationReaderBase& reader) {
	m_configValues = reader.GetConfigValues();
}

bool Configuration::Get(const std::string& key, std::string & var)
{
	auto it = m_configValues.find(key);
	if (it == m_configValues.end())
		return false;

	std::stringstream(it->second) >> var;
	return true;
}

bool Configuration::Get(const std::string & key, bool & var)
{
	auto it = m_configValues.find(key);
	if (it == m_configValues.end())
		return false;

	std::stringstream(it->second) >> std::boolalpha >> var;
	return true;
}

bool Configuration::Get(const std::string& key, char & var)
{
	auto it = m_configValues.find(key);
	if (it == m_configValues.end())
		return false;

	std::stringstream(it->second) >> var;
	return true;
}

bool Configuration::Get(const std::string& key, unsigned char & var)
{
	return false;
}

bool Configuration::Get(const std::string& key, short & var)
{
	return false;
}

bool Configuration::Get(const std::string& key, unsigned short & var)
{
	return false;
}

bool Configuration::Get(const std::string& key, int & var)
{
	auto it = m_configValues.find(key);
	if (it == m_configValues.end())
		return false;

	std::stringstream(it->second) >> var;
	return true;
}

bool Configuration::Get(const std::string& key, unsigned int & var)
{
	return false;
}

bool Configuration::Get(const std::string& key, long & var)
{
	return false;
}

bool Configuration::Get(const std::string& key, unsigned long & var)
{
	return false;
}

bool Configuration::Get(const std::string& key, double & var)
{
	return false;
}
