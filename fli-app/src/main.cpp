#include <iostream>

#include "Vulkan.hpp"
#include "config_reader.hpp"
#include "logger_simple.hpp"

int main() {
	fli::util::config::ConfigurationReader reader(std::ifstream("config.txt"));
	fli::util::config::Configuration config(reader);
	std::ofstream logFile("log.txt");
	fli::util::log::SimpleLogger logger(logFile, fli::util::log::LogLvl::all);

	try {
		Vulkan vulkan(logger, config);
	}
	catch (VulkanException ex) {
		std::cerr << ex.what() << std::endl;
	}

	logFile.close();
}