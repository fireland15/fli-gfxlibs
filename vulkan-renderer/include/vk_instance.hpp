#pragma once

#include "logger_base.hpp"
#include "configuration.hpp"
#include "vk_tostrings.hpp"
#include "vk_device.hpp"
#include "exceptions\vk_exceptions.hpp"

#include "vulkan.h"

typedef fli::util::log::LoggerBase Logger_t;
typedef fli::util::log::LogEntry LogEntry_t;
typedef fli::util::log::LogLvl LogLvl;
typedef fli::util::config::Configuration Config_t;

class VulkanInstance {
private:
	Logger_t& m_logger;
	Config_t& m_config;

	VkInstance m_instance;

public:
	VulkanInstance(Logger_t& logger, Config_t& config);
	~VulkanInstance();

	bool Create();
	VulkanDevice GetDevice();
};