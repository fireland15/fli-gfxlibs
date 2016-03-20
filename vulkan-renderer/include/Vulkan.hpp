#pragma once

#include "logger_base.hpp"
#include "config_reader_base.hpp"

#include "vulkan.h"

typedef fli::util::log::LoggerBase Logger_t;
typedef fli::util::log::LogEntry LogEntry_t;
typedef fli::util::log::LogLvl LogLvl;
typedef fli::util::config::ConfigurationReaderBase Config_t;

class Vulkan {
private:
	Logger_t& m_logger;
	Config_t& m_config;
public:
	Vulkan(Logger_t& logger, Config_t& config);
};