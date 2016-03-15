#pragma once

#include <map>
#include <string>
#include <sstream>

#include "config_reader_base.hpp"

namespace fli {
	namespace util {
		namespace config {

			/// <summary>
			/// Class for reading (and eventually setting) configuration values.
			/// </summary>
			class Configuration {
			private:
				/// <summary>
				/// A map of configuration values and their keys.
				/// </summary>
				std::map<std::string, std::string> m_configValues;
				
			public:
				/// <summary>
				/// Default Constructor. Requires reassignment by another constructor later.
				/// </summary>
				Configuration();

				/// <summary>
				/// Constructor that uses the provided reader to read and set the configuration values.
				/// </summary>
				/// <param name="reader">Reader to read configuration values and put them in the container.</param>
				Configuration(ConfigurationReaderBase& reader);

				/// <summary>
				/// Get the specified configuration value.
				/// </summary>
				/// <param name="key">The name of the configuration value.</param>
				/// <param name="var">A variable to hold the configuration value if it exists.</param>
				/// <returns>A result indicating if there was a configuration value matching the supplied key.</returns>
				bool Get(const std::string& key, std::string& var);

				/// <summary>
				/// Get the specified configuration value.
				/// </summary>
				/// <param name="key">The name of the configuration value.</param>
				/// <param name="var">A variable to hold the configuration value if it exists.</param>
				/// <returns>A result indicating if there was a configuration value matching the supplied key.</returns>
				bool Get(const std::string& key, bool& var);

				/// <summary>
				/// Get the specified configuration value.
				/// </summary>
				/// <param name="key">The name of the configuration value.</param>
				/// <param name="var">A variable to hold the configuration value if it exists.</param>
				/// <returns>A result indicating if there was a configuration value matching the supplied key.</returns>
				bool Get(const std::string& key, char& var);

				/// <summary>
				/// Get the specified configuration value.
				/// </summary>
				/// <param name="key">The name of the configuration value.</param>
				/// <param name="var">A variable to hold the configuration value if it exists.</param>
				/// <returns>A result indicating if there was a configuration value matching the supplied key.</returns>
				bool Get(const std::string& key, unsigned char& var);

				/// <summary>
				/// Get the specified configuration value.
				/// </summary>
				/// <param name="key">The name of the configuration value.</param>
				/// <param name="var">A variable to hold the configuration value if it exists.</param>
				/// <returns>A result indicating if there was a configuration value matching the supplied key.</returns>
				bool Get(const std::string& key, short& var);

				/// <summary>
				/// Get the specified configuration value.
				/// </summary>
				/// <param name="key">The name of the configuration value.</param>
				/// <param name="var">A variable to hold the configuration value if it exists.</param>
				/// <returns>A result indicating if there was a configuration value matching the supplied key.</returns>
				bool Get(const std::string& key, unsigned short& var);

				/// <summary>
				/// Get the specified configuration value.
				/// </summary>
				/// <param name="key">The name of the configuration value.</param>
				/// <param name="var">A variable to hold the configuration value if it exists.</param>
				/// <returns>A result indicating if there was a configuration value matching the supplied key.</returns>
				bool Get(const std::string& key, int& var);

				/// <summary>
				/// Get the specified configuration value.
				/// </summary>
				/// <param name="key">The name of the configuration value.</param>
				/// <param name="var">A variable to hold the configuration value if it exists.</param>
				/// <returns>A result indicating if there was a configuration value matching the supplied key.</returns>
				bool Get(const std::string& key, unsigned int& var);

				/// <summary>
				/// Get the specified configuration value.
				/// </summary>
				/// <param name="key">The name of the configuration value.</param>
				/// <param name="var">A variable to hold the configuration value if it exists.</param>
				/// <returns>A result indicating if there was a configuration value matching the supplied key.</returns>
				bool Get(const std::string& key, long& var);

				/// <summary>
				/// Get the specified configuration value.
				/// </summary>
				/// <param name="key">The name of the configuration value.</param>
				/// <param name="var">A variable to hold the configuration value if it exists.</param>
				/// <returns>A result indicating if there was a configuration value matching the supplied key.</returns>
				bool Get(const std::string& key, unsigned long& var);

				/// <summary>
				/// Get the specified configuration value.
				/// </summary>
				/// <param name="key">The name of the configuration value.</param>
				/// <param name="var">A variable to hold the configuration value if it exists.</param>
				/// <returns>A result indicating if there was a configuration value matching the supplied key.</returns>
				bool Get(const std::string& key, float& var);

				/// <summary>
				/// Get the specified configuration value.
				/// </summary>
				/// <param name="key">The name of the configuration value.</param>
				/// <param name="var">A variable to hold the configuration value if it exists.</param>
				/// <returns>A result indicating if there was a configuration value matching the supplied key.</returns>
				bool Get(const std::string& key, double& var);
			};

		}
	}
}