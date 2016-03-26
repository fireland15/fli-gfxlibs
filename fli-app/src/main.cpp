#include <iostream>

#include "Vulkan.hpp"
#include "config_reader.hpp"
#include "logger_simple.hpp"

int main() {
	std::ofstream logFile("log.txt");
	std::ifstream configFile("config.txt");

	{
		fli::util::config::ConfigurationReader reader(configFile);
		fli::util::config::Configuration config(reader);
		fli::util::log::SimpleLogger logger(logFile, fli::util::log::LogLvl::all);

		try {
			Vulkan vulkan(logger, config);
		}
		catch (VulkanException ex) {
			std::cerr << ex.what() << std::endl;
		}
	}

	configFile.close();
	logFile.close();
}