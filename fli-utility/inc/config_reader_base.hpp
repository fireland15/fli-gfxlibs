#include <string>
#include <map>

#pragma once

namespace fli {
	namespace util {
		namespace config {

			class ConfigurationReaderBase {
			public:
				/// <summary>
				/// Sets configuration values in a std::map
				/// </summary>
				/// <returns>A map of config keys and values</returns>
				virtual std::map<std::string, std::string> GetConfigValues() = 0;
			};
		}
	}
}