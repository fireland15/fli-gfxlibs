#include "configuration.hpp"

namespace fli {
	namespace util {
		namespace config {

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
				auto it = m_configValues.find(key);
				if (it == m_configValues.end())
					return false;
				unsigned int temp;
				std::stringstream(it->second) >> temp;
				var = (unsigned char)temp;
				return true;
			}

			bool Configuration::Get(const std::string& key, short & var)
			{
				auto it = m_configValues.find(key);
				if (it == m_configValues.end())
					return false;
				std::stringstream(it->second) >> var;
				return true;
			}

			bool Configuration::Get(const std::string& key, unsigned short & var)
			{
				auto it = m_configValues.find(key);
				if (it == m_configValues.end())
					return false;
				std::stringstream(it->second) >> var;
				return true;
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
				auto it = m_configValues.find(key);
				if (it == m_configValues.end())
					return false;

				std::stringstream(it->second) >> var;
				return true;
			}

			bool Configuration::Get(const std::string& key, long & var)
			{
				auto it = m_configValues.find(key);
				if (it == m_configValues.end())
					return false;

				std::stringstream(it->second) >> var;
				return true;
			}

			bool Configuration::Get(const std::string& key, unsigned long & var)
			{
				auto it = m_configValues.find(key);
				if (it == m_configValues.end())
					return false;

				std::stringstream(it->second) >> var;
				return true;
			}

			bool Configuration::Get(const std::string & key, float & var)
			{
				auto it = m_configValues.find(key);
				if (it == m_configValues.end())
					return false;

				std::stringstream(it->second) >> var;
				return true;
			}

			bool Configuration::Get(const std::string& key, double & var)
			{
				auto it = m_configValues.find(key);
				if (it == m_configValues.end())
					return false;

				std::stringstream(it->second) >> var;
				return true;
			}

		}
	}
}
