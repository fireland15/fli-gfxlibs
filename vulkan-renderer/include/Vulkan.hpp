#pragma once

#include "logger_base.hpp"
#include "configuration.hpp"

#include "vk_instance.hpp"

class Vulkan {
private:
	Logger_t& m_logger;
	Config_t& m_config;

	VulkanInstance* m_pInstance;
public:
	Vulkan(Logger_t& logger, Config_t& config);
};